<?php
/**
 * @file for Add new term
 */

/**
 * Implements hook_form(), callback from hook_menu()
 * add new taxonomy term for 'Client' which vocabulary is 2
 */
function clientterm_add_new_term_form() {
  $form_id = 'taxonomy_form_term';

  module_load_include('inc', 'taxonomy', 'taxonomy.admin');
  $vocabulary = taxonomy_vocabulary_load(2);

  $edit = array();
  $form = drupal_get_form($form_id, $edit, $vocabulary);

  /** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
  global $user;
  if (!in_array('administrator', $user->roles)) {
    $form['description']['#access'] = FALSE;
    $form['relations']['#attributes']['class'][] = 'element-hidden';
  }
  // add "col-sm-6" class for below field
  $fields_name = array(
    'name',
    'field_client_contactname',
    'field_client_contactphone',
    'field_client_contactemail',
    'field_client_province',
    'field_client_contactaddress',
    'field_client_clienttype',
  );

  foreach ($fields_name as $row_name) {
    $form[$row_name]['#prefix'] = '<div class="col-sm-6">';
    $form[$row_name]['#suffix'] = '</div>';
  }

  $form['actions']['submit']['#prefix'] = '<div class="row text-center clear-both">';
  $form['actions']['submit']['#suffix'] = '</div>';
  $form['actions']['submit']['#attributes']['class'][] = 'margin-top-24';
  /** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

  $output = drupal_render($form);

  return $output;
}
