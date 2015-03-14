<?php
/**
 * @file
 */

/**
 * callback from hook_menu()
 * Embed Views to output content
 */
function repairtype_print_tab_page($nid = NULL) {
  if (empty($nid) || !is_numeric($nid)) {
    return t('You have to select one of page');
  }

  $node = node_load($nid);
  if (!$node) {
    return t('Please select right repair number');
  }
  if ($node->type != 'repair') {
    return t('Please select right repair number');
  }

  $output = '';
  if (theme_get_setting('logo')) {
    $image = array(
      'path' => theme_get_setting('logo'),
      'alt' => 'my logo',
      'attributes' => array('class' => 'text-center'),
    );
    $logo = theme('image', $image); 
    $output .= '<div class="visible-print margin-bottom-24">' . $logo . '</div>';
  }
  $output .= views_embed_view('repair_print_table', 'default', $nid);

  // add print button
  $output .= '<div class="btn btn-success repair-node-print-button hidden-print" type="button">' . t('Print') . '</div>';
  drupal_add_js('jQuery(document).ready(function () {
      jQuery(".repair-node-print-button").click(function(){
        window.print();
        return false;
      });
    });',
    'inline'
  );
  return $output;
}