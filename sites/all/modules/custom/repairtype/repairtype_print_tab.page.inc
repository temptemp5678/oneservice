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
  $output .= views_embed_view('repair_print_table', 'default', $nid);
  return $output;
}