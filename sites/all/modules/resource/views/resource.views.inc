<?php

/**
 * @file
 * Providing extra functionality for the Resource UI via views.
 */


/**
 * Implements hook_views_data()
 */
function resource_views_data_alter(&$data) { 
  $data['resource']['link_resource'] = array(
    'field' => array(
      'title' => t('Link'),
      'help' => t('Provide a link to the Learning Resource.'),
      'handler' => 'resource_handler_link_field',
    ),
  );
  $data['resource']['edit_resource'] = array(
    'field' => array(
      'title' => t('Edit Link'),
      'help' => t('Provide a link to the edit form for the Learning Resource.'),
      'handler' => 'resource_handler_edit_link_field',
    ),
  );
  $data['resource']['delete_resource'] = array(
    'field' => array(
      'title' => t('Delete Link'),
      'help' => t('Provide a link to delete the Learning Resource.'),
      'handler' => 'resource_handler_delete_link_field',
    ),
  );
  // This content of this field are decided based on the menu structure that
  // follows resources/resource/%resource_id/op
  $data['resource']['operations'] = array(
    'field' => array(
      'title' => t('Operations links'),
      'help' => t('Display all operations available for this Learning Resource.'),
      'handler' => 'resource_handler_resource_operations_field',
    ),
  );
}


/**
 * Implements hook_views_default_views().
 */
function resource_views_default_views() {
  $views = array();

$view = new view();
$view->name = 'resources';
$view->description = 'A list of all resources';
$view->tag = 'resources';
$view->base_table = 'resource';
$view->human_name = 'Resources';
$view->core = 7;
$view->api_version = '3.0';
$view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

/* Display: Master */
$handler = $view->new_display('default', 'Master', 'default');
$handler->display->display_options['title'] = 'Learning Resources';
$handler->display->display_options['use_more_always'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'administer resources';
$handler->display->display_options['cache']['type'] = 'none';
$handler->display->display_options['query']['type'] = 'views_query';
$handler->display->display_options['exposed_form']['type'] = 'basic';
$handler->display->display_options['pager']['type'] = 'full';
$handler->display->display_options['pager']['options']['items_per_page'] = '10';
$handler->display->display_options['style_plugin'] = 'table';
$handler->display->display_options['style_options']['columns'] = array(
  'name' => 'name',
  'resource_id' => 'resource_id',
);
$handler->display->display_options['style_options']['default'] = '-1';
$handler->display->display_options['style_options']['info'] = array(
  'name' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
  'resource_id' => array(
    'sortable' => 0,
    'default_sort_order' => 'asc',
    'align' => '',
    'separator' => '',
  ),
);
/* No results behavior: Global: Text area */
$handler->display->display_options['empty']['area']['id'] = 'area';
$handler->display->display_options['empty']['area']['table'] = 'views';
$handler->display->display_options['empty']['area']['field'] = 'area';
$handler->display->display_options['empty']['area']['label'] = 'Empty ';
$handler->display->display_options['empty']['area']['content'] = 'No resources have been created yet';
/* Field: Learning Resource: Learning resource ID */
$handler->display->display_options['fields']['resource_id']['id'] = 'resource_id';
$handler->display->display_options['fields']['resource_id']['table'] = 'resource';
$handler->display->display_options['fields']['resource_id']['field'] = 'resource_id';
/* Field: Learning Resource: Name */
$handler->display->display_options['fields']['name']['id'] = 'name';
$handler->display->display_options['fields']['name']['table'] = 'resource';
$handler->display->display_options['fields']['name']['field'] = 'name';
/* Field: Learning Resource: Link */
$handler->display->display_options['fields']['link_resource']['id'] = 'link_resource';
$handler->display->display_options['fields']['link_resource']['table'] = 'resource';
$handler->display->display_options['fields']['link_resource']['field'] = 'link_resource';
$handler->display->display_options['fields']['link_resource']['label'] = 'View';
/* Field: Learning Resource: Operations links */
$handler->display->display_options['fields']['operations']['id'] = 'operations';
$handler->display->display_options['fields']['operations']['table'] = 'resource';
$handler->display->display_options['fields']['operations']['field'] = 'operations';

/* Display: Page */
$handler = $view->new_display('page', 'Page', 'resources_admin_page');
$handler->display->display_options['path'] = 'admin/content/resources/list';
$handler->display->display_options['menu']['type'] = 'default tab';
$handler->display->display_options['menu']['title'] = 'List';
$handler->display->display_options['menu']['weight'] = '-10';
$handler->display->display_options['tab_options']['type'] = 'tab';
$handler->display->display_options['tab_options']['title'] = 'Learning Resource';
$handler->display->display_options['tab_options']['description'] = 'Manage Learning Resource';
$handler->display->display_options['tab_options']['weight'] = '0';
$handler->display->display_options['tab_options']['name'] = 'management';

/* Display: Own resources */
$handler = $view->new_display('page', 'Own resources', 'page_1');
$handler->display->display_options['defaults']['access'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'administer own resources';
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Field: Learning Resource: Learning resource ID */
$handler->display->display_options['fields']['resource_id']['id'] = 'resource_id';
$handler->display->display_options['fields']['resource_id']['table'] = 'resource';
$handler->display->display_options['fields']['resource_id']['field'] = 'resource_id';
/* Field: Learning Resource: Name */
$handler->display->display_options['fields']['name']['id'] = 'name';
$handler->display->display_options['fields']['name']['table'] = 'resource';
$handler->display->display_options['fields']['name']['field'] = 'name';
/* Field: Learning Resource: Link */
$handler->display->display_options['fields']['link_resource']['id'] = 'link_resource';
$handler->display->display_options['fields']['link_resource']['table'] = 'resource';
$handler->display->display_options['fields']['link_resource']['field'] = 'link_resource';
$handler->display->display_options['fields']['link_resource']['label'] = 'View';
/* Field: Learning Resource: Operations links */
$handler->display->display_options['fields']['operations']['id'] = 'operations';
$handler->display->display_options['fields']['operations']['table'] = 'resource';
$handler->display->display_options['fields']['operations']['field'] = 'operations';
/* Field: Learning Resource: Uid */
$handler->display->display_options['fields']['uid']['id'] = 'uid';
$handler->display->display_options['fields']['uid']['table'] = 'resource';
$handler->display->display_options['fields']['uid']['field'] = 'uid';
$handler->display->display_options['fields']['uid']['exclude'] = TRUE;
$handler->display->display_options['defaults']['filter_groups'] = FALSE;
$handler->display->display_options['defaults']['filters'] = FALSE;
/* Filter criterion: Global: PHP */
$handler->display->display_options['filters']['php']['id'] = 'php';
$handler->display->display_options['filters']['php']['table'] = 'views';
$handler->display->display_options['filters']['php']['field'] = 'php';
$handler->display->display_options['filters']['php']['use_php_setup'] = 0;
$handler->display->display_options['filters']['php']['php_filter'] = 'GLOBAL $user;
if($user->uid != $row->uid){
return true;
}';
$handler->display->display_options['path'] = 'admin/content/resources/my';
$handler->display->display_options['menu']['type'] = 'default tab';
$handler->display->display_options['menu']['title'] = 'List';
$handler->display->display_options['menu']['weight'] = '-10';
$handler->display->display_options['tab_options']['type'] = 'tab';
$handler->display->display_options['tab_options']['title'] = 'Learning Resource';
$handler->display->display_options['tab_options']['description'] = 'Manage Learning Resource';
$handler->display->display_options['tab_options']['weight'] = '0';
$handler->display->display_options['tab_options']['name'] = 'management';

/* Display: Entity Reference */
$handler = $view->new_display('entityreference', 'Entity Reference', 'entityreference_1');
$handler->display->display_options['defaults']['title'] = FALSE;
$handler->display->display_options['title'] = 'Learning Resources';
$handler->display->display_options['defaults']['access'] = FALSE;
$handler->display->display_options['access']['type'] = 'perm';
$handler->display->display_options['access']['perm'] = 'administer own resources';
$handler->display->display_options['pager']['type'] = 'some';
$handler->display->display_options['defaults']['style_plugin'] = FALSE;
$handler->display->display_options['style_plugin'] = 'entityreference_style';
$handler->display->display_options['style_options']['search_fields'] = array(
  'name' => 'name',
  'uid' => 0,
);
$handler->display->display_options['defaults']['style_options'] = FALSE;
$handler->display->display_options['defaults']['row_plugin'] = FALSE;
$handler->display->display_options['row_plugin'] = 'entityreference_fields';
$handler->display->display_options['defaults']['row_options'] = FALSE;
$handler->display->display_options['defaults']['fields'] = FALSE;
/* Field: Learning Resource: Name */
$handler->display->display_options['fields']['name']['id'] = 'name';
$handler->display->display_options['fields']['name']['table'] = 'resource';
$handler->display->display_options['fields']['name']['field'] = 'name';
$handler->display->display_options['fields']['name']['label'] = '';
$handler->display->display_options['fields']['name']['element_label_colon'] = FALSE;
/* Field: Learning Resource: Uid */
$handler->display->display_options['fields']['uid']['id'] = 'uid';
$handler->display->display_options['fields']['uid']['table'] = 'resource';
$handler->display->display_options['fields']['uid']['field'] = 'uid';
$handler->display->display_options['fields']['uid']['label'] = '';
$handler->display->display_options['fields']['uid']['exclude'] = TRUE;
$handler->display->display_options['fields']['uid']['element_label_colon'] = FALSE;
$handler->display->display_options['defaults']['filter_groups'] = FALSE;
$handler->display->display_options['defaults']['filters'] = FALSE;
/* Filter criterion: Global: PHP */
$handler->display->display_options['filters']['php']['id'] = 'php';
$handler->display->display_options['filters']['php']['table'] = 'views';
$handler->display->display_options['filters']['php']['field'] = 'php';
$handler->display->display_options['filters']['php']['use_php_setup'] = 0;
$handler->display->display_options['filters']['php']['php_filter'] = 'GLOBAL $user;
if (in_array("resource editor", $user->roles)) { 
if($user->uid != $row->uid){
return true;
}
}else{ 
return false;
}';



  $translatables['resources'] = array(
    t('Master'),
    t('Learning Resources'),
    t('more'),
    t('Apply'),
    t('Reset'),
    t('Sort by'),
    t('Asc'),
    t('Desc'),
    t('Items per page'),
    t('- All -'),
    t('Offset'),
    t('Empty '),
    t('No Learning Resources have been created yet'),
    t('Learning Resources ID'),
    t('.'),
    t(','),
    t('Name'),
    t('View'),
    t('Operations links'),
    t('Page'),
  );
  $views[$view->name] = $view;
  return $views;

}
