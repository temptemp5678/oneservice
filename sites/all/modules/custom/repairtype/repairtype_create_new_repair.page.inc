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

  $form = drupal_build_form($form_id, $form_state);
  return $form;
}

function repairtype_create_new_repair22() {
  // content type name
  $type = 'repair';
  module_load_include('inc', 'node', 'node.pages');
  $form = node_add($type);

  $form['field_repair_client_contactphone']['und'][0]['value']['#attributes']['placeholder'] = 'Phone Number';

  return $form;
}

function repairtype_create_new_repair33() {
  // content type name
  $type = 'repair';

  global $user;
  $node = (object) array(
    'uid' => $user->uid,
    'name' => (isset($user->name) ? $user->name : ''),
    'type' => $type,
    'language' => LANGUAGE_NONE,
  );

  // Invoke hook_nodapi and hook_node
  node_object_prepare($node);

  module_load_include('inc', 'node', 'node.pages');
  $form = drupal_get_form($type . '_node_form', $node);

  return drupal_render($form);
}