<?php

/**
 * @file
 * Contains a Views field handler to take care of displaying edit links
 * as fields
 */


class resource_handler_edit_link_field extends resource_handler_link_field {
  function construct() {
    parent::construct();
    $this->additional_fields['type'] = 'type';
  }

  function render($values) {
    $type = $values->{$this->aliases['type']};
    
    //Creating a dummy resource to check access against
    $dummy_resource = (object) array('type' => $type);
    if (!resource_access('edit', $dummy_resource)) {
      return;
    }
    
    $text = !empty($this->options['text']) ? $this->options['text'] : t('edit');
    $resource_id = $values->{$this->aliases['resource_id']};
    
    return l($text, 'admin/content/resources/resource/' . $resource_id . '/edit');
  }
}
