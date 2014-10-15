<?php

/**
 * @file
 * Example tpl file for theming a single resource-specific theme
 *
 * Available variables:
 * - $status: The variable to theme (while only show if you tick status)
 * 
 * Helper variables:
 * - $resource: The Resource object this status is derived from
 */
?>

<div class="resource-status">
  <?php print '<strong>Resource Sample Data:</strong> ' . $resource_sample_data = ($resource_sample_data) ? 'Switch On' : 'Switch Off' ?>
</div>