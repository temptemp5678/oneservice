<?php
/**
 * @file for Add new term
 */

/**
 * Implements hook_form(), callback from hook_menu()
 * add new taxonomy term for 'Device Type' which vocabulary is 3
 */
function otherterm_add_term_device() {
  $form_id = 'taxonomy_form_term';

  module_load_include('inc', 'taxonomy', 'taxonomy.admin');
  $vocabulary = taxonomy_vocabulary_load(3);

  $edit = array();
  $form = drupal_get_form($form_id, $edit, $vocabulary);

  /** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
  global $user;
  if (!in_array('administrator', $user->roles)) {
    $form['relations']['#attributes']['class'][] = 'element-hidden';
  }

  $form['name']['#attributes']['placeholder'] = 'Client Title';
  $form['description']['value']['#attributes']['placeholder'] = 'Client Description';
  $form['description']['format']['#access'] = FALSE;

  /** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
  $output = drupal_render($form);

  return $output;
}
