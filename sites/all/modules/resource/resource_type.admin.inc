<?php

/**
 * @file
 * Resource type editing UI.
 */

/**
 * UI controller.
 */
class ResourceTypeUIController extends EntityDefaultUIController {

  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
		$items[$this->path]['description'] = 'Manage resource entity types, including adding
		and removing fields and the display of fields.';
    return $items;
  }
}

/**
 * Generates the resource type editing form.
 */
function resource_type_form($form, &$form_state, $resource_type, $op = 'edit') {

  if ($op == 'clone') {
    $resource_type->label .= ' (cloned)';
    $resource_type->type = '';
  }

  $form['label'] = array(
    '#title' => t('Label'),
    '#type' => 'textfield',
    '#default_value' => $resource_type->label,
    '#description' => t('The human-readable name of this Learning Resource type.'),
    '#required' => TRUE,
    '#size' => 30,
  );
  // Machine-readable type name.
  $form['type'] = array(
    '#type' => 'machine_name',
    '#default_value' => isset($resource_type->type) ? $resource_type->type : '',
    '#maxlength' => 32,
//    '#disabled' => $resource_type->isLocked() && $op != 'clone',
    '#machine_name' => array(
      'exists' => 'resource_get_types',
      'source' => array('label'),
    ),
    '#description' => t('A unique machine-readable name for this Learning Resource type. It must only contain lowercase letters, numbers, and underscores.'),
  );

  $form['data']['#tree'] = TRUE;
  $form['data']['sample_data'] = array(
    '#type' => 'checkbox',
    '#title' => t('An interesting Learning Resource switch'),
    '#default_value' => !empty($resource_type->data['sample_data']),
  );

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save Learning Resource type'),
    '#weight' => 40,
  );

  //Locking not supported yet
  /*if (!$resource_type->isLocked() && $op != 'add') {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete resource type'),
      '#weight' => 45,
      '#limit_validation_errors' => array(),
      '#submit' => array('resource_type_form_submit_delete')
    );
  }*/
  return $form;
}

/**
 * Form API submit callback for the type form.
 */
function resource_type_form_submit(&$form, &$form_state) {
  $resource_type = entity_ui_form_submit_build_entity($form, $form_state);
  $resource_type->save();
  $form_state['redirect'] = 'admin/structure/resource_types';
}

/**
 * Form API submit callback for the delete button.
 */
function resource_type_form_submit_delete(&$form, &$form_state) {
  $form_state['redirect'] = 'admin/structure/resource_types/manage/' . $form_state['resource_type']->type . '/delete';
}
