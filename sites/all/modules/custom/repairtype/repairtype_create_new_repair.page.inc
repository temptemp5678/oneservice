<?php
/**
 * @file for Add new term
 */

/**
 * Implements hook_form(), callback from hook_menu()
 * add new taxonomy term for 'Client' which vocabulary is 2
 */
function repairtype_create_new_repair() {
  $form_id = 'repair_node_form';

  global $user;
  $node = (object) array(
    'uid' => $user->uid,
    'name' => (isset($user->name) ? $user->name : ''),
    'type' => 'repair',               // content type name
    'language' => LANGUAGE_NONE,
  );
  $form_state['build_info']['args'] = array($node);
  form_load_include($form_state, 'inc', 'node', 'node.pages');

  $output = drupal_build_form($form_id, $form_state);
  return $output;
}
