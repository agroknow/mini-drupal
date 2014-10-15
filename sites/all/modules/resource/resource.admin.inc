<?php

/**
 * @file
 * Resource editing UI.
 *
 * We make very little use of the EntityAPI interface for this - preferring instead to use
 * views. That offers more flexibility to change a UI that will, more often than not,
 * be end-user facing.
 */

/**
 * UI controller.
 */
class ResourceUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults. Main reason for doing this is that
   * parent class hook_menu() is optimized for entity type administration.
   */
  public function hook_menu() {
    
    $items = array();
    $id_count = count(explode('/', $this->path));
    $wildcard = isset($this->entityInfo['admin ui']['menu wildcard']) ? $this->entityInfo['admin ui']['menu wildcard'] : '%' . $this->entityType;

    $items[$this->path] = array(
      'title' => 'Learning Resources',
      'description' => 'Add edit and update learning scenarios.',
      'page callback' => 'system_admin_menu_block_page',
      'access arguments' => array('access administration pages'),
      'file path' => drupal_get_path('module', 'system'),
      'file' => 'system.admin.inc',
    );
    
    // Change the overview menu type for the list of resources.
    $items[$this->path]['type'] = MENU_LOCAL_TASK;
    
    // Change the add page menu to multiple types of entities
    $items[$this->path . '/add'] = array(
      'title' => 'Add a Learning Resource',
      'description' => 'Add a new Learning Resource',
      'page callback'  => 'resource_add_page',
      'access callback'  => 'resource_access',
      'access arguments' => array('add'),
      'type' => MENU_NORMAL_ITEM,
      'weight' => 20,
      'file' => 'resource.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])

    );
    
    // Add menu items to add each different type of entity.
    foreach (resource_get_types() as $type) {
      $items[$this->path . '/add/' . $type->type] = array(
        'title' => 'Add ' . $type->label,
        'page callback' => 'resource_form_wrapper',
        'page arguments' => array(resource_create(array('type' => $type->type))),
        'access callback' => 'resource_access',
        'access arguments' => array('add', 'edit ' . $type->type),
        'file' => 'resource.admin.inc',
        'file path' => drupal_get_path('module', $this->entityInfo['module'])
      );
    }

    // Loading and editing resource entities
    $items[$this->path . '/resource/' . $wildcard] = array(
      'page callback' => 'resource_form_wrapper',
      'page arguments' => array($id_count + 1),
      'access callback' => 'resource_access',
      'access arguments' => array('edit resource', $id_count + 1),
      'weight' => 0,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
      'file' => 'resource.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );
    $items[$this->path . '/resource/' . $wildcard . '/edit'] = array(
      'title' => 'Edit',
      'type' => MENU_DEFAULT_LOCAL_TASK,
      'weight' => -10,
      'context' => MENU_CONTEXT_PAGE | MENU_CONTEXT_INLINE,
    );
    
    $items[$this->path . '/resource/' . $wildcard . '/delete'] = array(
      'title' => 'Delete',
      'page callback' => 'resource_delete_form_wrapper',
      'page arguments' => array($id_count + 1),
      'access callback' => 'resource_access',
      'access arguments' => array('delete', $id_count + 1),
      'type' => MENU_LOCAL_TASK,
      'context' => MENU_CONTEXT_INLINE,
      'weight' => 10,
      'file' => 'resource.admin.inc',
      'file path' => drupal_get_path('module', $this->entityInfo['module'])
    );
    
    // Menu item for viewing resources
    $items['resource/' . $wildcard] = array(
      //'title' => 'Title',
      'title callback' => 'resource_page_title',
      'title arguments' => array(1),
      'page callback' => 'resource_page_view',
      'page arguments' => array(1),
      'access callback' => 'resource_access',
      'access arguments' => array('view', 1),
      'type' => MENU_CALLBACK,
    );
    return $items;
  }
  
  
  /**
   * Create the markup for the add Resource Entities page within the class
   * so it can easily be extended/overriden.
   */ 
  public function addPage() {
    $item = menu_get_item();
    $content = system_admin_menu_block($item);

    if (count($content) == 1) {
      $item = array_shift($content);
      drupal_goto($item['href']);
    }    
        
    return theme('resource_add_list', array('content' => $content));
  }
  
}


/**
 * Form callback wrapper: create or edit a resource.
 *
 * @param $resource
 *   The resource object being edited by this form.
 *
 * @see resource_edit_form()
 */
function resource_form_wrapper($resource) {
  // Add the breadcrumb for the form's location.
  resource_set_breadcrumb();
  return drupal_get_form('resource_edit_form', $resource);
}


/**
 * Form callback wrapper: delete a resource.
 *
 * @param $resource
 *   The resource object being edited by this form.
 *
 * @see resource_edit_form()
 */
function resource_delete_form_wrapper($resource) {
  // Add the breadcrumb for the form's location.
  //resource_set_breadcrumb();
  return drupal_get_form('resource_delete_form', $resource);
}


/**
 * Form callback: create or edit a resource.
 *
 * @param $resource
 *   The resource object to edit or for a create form an empty resource object
 *     with only a resource type defined.
 */
function resource_edit_form($form, &$form_state, $resource) {
  // Add the default field elements.
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Learning Resource Name'),
    '#default_value' => isset($resource->name) ? $resource->name : '',
    '#maxlength' => 255,
    '#required' => TRUE,
    '#weight' => -5,
  );
  GLOBAL $user;
   $form['uid'] = array(
    '#type' => 'hidden',
    //'#title' => t('Learning Resource Name'),
    '#default_value' => isset($resource->uid) ? $resource->uid : $user->uid,
//    '#maxlength' => 255,
    '#required' => TRUE,
    '#weight' => -5,
  );


   $form['public'] = array(
     '#type' => 'radios',
    '#title' => t('Visibility'),
    '#default_value' => isset($resource->public) ? $resource->public : NULL,
//    '#maxlength' => 255,
    '#required' => FALSE,
    '#weight' => -5,
    '#options' => array(0 => t('Private'), 1 => t('Public')),
  );
  
  $form['data']['#tree'] = TRUE;
  $form['data']['sample_data'] = array(
    '#type' => 'hidden',
    '#title' => t('An interesting Learning Resource switch'),
    '#default_value' => isset($resource->data['sample_data']) ? $resource->data['sample_data'] : 1,
  );

  // Add the field related form elements.
  $form_state['resource'] = $resource;
  field_attach_form('resource', $resource, $form, $form_state);

  $form['actions'] = array(
    '#type' => 'container',
    '#attributes' => array('class' => array('form-actions')),
    '#weight' => 400,
  );

  // We add the form's #submit array to this button along with the actual submit
  // handler to preserve any submit handlers added by a form callback_wrapper.
  $submit = array();

  if (!empty($form['#submit'])) {
    $submit += $form['#submit'];
  }

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Learning Resource'),
    '#submit' => $submit + array('resource_edit_form_submit'),
  );
  
  if (!empty($resource->name)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete Learning Resource'),
      '#suffix' => l(t('Cancel'), 'admin/content/resources'),
      '#submit' => $submit + array('resource_form_submit_delete'),
      '#weight' => 45,
    );
  }

  // We append the validate handler to #validate in case a form callback_wrapper
  // is used to add validate handlers earlier.
  $form['#validate'][] = 'resource_edit_form_validate';
  return $form;
}


/**
 * Form API validate callback for the resource form
 */
function resource_edit_form_validate(&$form, &$form_state) {
  $resource = $form_state['resource'];
  
  // Notify field widgets to validate their data.
  field_attach_form_validate('resource', $resource, $form, $form_state);
}


/**
 * Form API submit callback for the resource form.
 * 
 * @todo remove hard-coded link
 */
function resource_edit_form_submit(&$form, &$form_state) {
  
  $resource = entity_ui_controller('resource')->entityFormSubmitBuildEntity($form, $form_state);
  // Save the resource and go back to the list of resources
  
  // Add in created and changed times.
  if ($resource->is_new = isset($resource->is_new) ? $resource->is_new : 0){
    $resource->created = time();
  }

  $resource->changed = time();
  
  $resource->save();
  $form_state['redirect'] = 'admin/content/resources';
}

/**
 * Form API submit callback for the delete button.
 * 
 * @todo Remove hard-coded path
 */
function resource_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/content/resources/resource/' . $form_state['resource']->resource_id . '/delete';
}


/**
 * Form callback: confirmation form for deleting a resource.
 *
 * @param $resource
 *   The resource to delete
 *
 * @see confirm_form()
 */
function resource_delete_form($form, &$form_state, $resource) {
  $form_state['resource'] = $resource;

  $form['#submit'][] = 'resource_delete_form_submit';

  $form = confirm_form($form,
    t('Are you sure you want to delete Learning Resource %name?', array('%name' => $resource->name)),
    'admin/content/resources/resource',
    '<p>' . t('This action cannot be undone.') . '</p>',
    t('Delete'),
    t('Cancel'),
    'confirm'
  );
  
  return $form;
}

/**
 * Submit callback for resource_delete_form
 */
function resource_delete_form_submit($form, &$form_state) {
  $resource = $form_state['resource'];

  resource_delete($resource);

  drupal_set_message(t('The Learning Resource %name has been deleted.', array('%name' => $resource->name)));
  watchdog('resource', 'Deleted Learning Resource %name.', array('%name' => $resource->name));

  $form_state['redirect'] = 'admin/content/resources';
}



/**
 * Page to add Resource Entities.
 *
 * @todo Pass this through a proper theme function
 */
function resource_add_page() {
  $controller = entity_ui_controller('resource');
  return $controller->addPage();
}


/**
 * Displays the list of available resource types for resource creation.
 *
 * @ingroup themeable
 */
function theme_resource_add_list($variables) {
  $content = $variables['content'];
  $output = '';
  if ($content) {
    $output = '<dl class="resource-type-list">';
    foreach ($content as $item) {
      $output .= '<dt>' . l($item['title'], $item['href']) . '</dt>';
      $output .= '<dd>' . filter_xss_admin($item['description']) . '</dd>';
    }
    $output .= '</dl>';
  }
  else {
    if (user_access('administer resource types')) {
      $output = '<p>' . t('Learning Resource Entities cannot be added because you have not created any resource types yet. Go to the <a href="@create-resource-type">resource type creation page</a> to add a new resource type.', array('@create-resource-type' => url('admin/structure/resource_types/add'))) . '</p>';
    }
    else {
      $output = '<p>' . t('No Learning Resource types have been created yet for you to use.') . '</p>';
    }
  }

  return $output;
}





/**
 * Sets the breadcrumb for administrative resource pages.
 */
function resource_set_breadcrumb() {
  $breadcrumb = array(
    l(t('Home'), '<front>'),
    l(t('Administration'), 'admin'),
    l(t('Content'), 'admin/content'),
    l(t('Learning Resource'), 'admin/content/resources'),
  );

  drupal_set_breadcrumb($breadcrumb);
}



