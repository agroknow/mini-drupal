<?php

/**
 * This field handler aggregates operations that can be done on a resource
 * under a single field providing a more flexible way to present them in a view
 */
class resource_handler_resource_operations_field extends views_handler_field {
  function construct() {
    parent::construct();

    $this->additional_fields['resource_id'] = 'resource_id';
  }

  function query() {
    $this->ensure_my_table();
    $this->add_additional_fields();
  }

  function render($values) {

    $links = menu_contextual_links('resource', 'admin/content/resources/resource', array($this->get_value($values, 'resource_id')));
    
    if (!empty($links)) {
      return theme('links', array('links' => $links, 'attributes' => array('class' => array('links', 'inline', 'operations'))));
    }
  }
}
