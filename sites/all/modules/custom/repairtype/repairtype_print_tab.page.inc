<?php
/**
 * @file
 */

/**
 * callback from hook_menu()
 * Embed Views to output content
 */
function repairtype_print_tab_page($nid) {
  $output = '';
  $output .= views_embed_view('repair_print_table', 'default', $nid);
  return $output;
}