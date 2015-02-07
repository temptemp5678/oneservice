<?php
/**
 * @file for Set default title of term
 */
/**
 * Implements hook_form(), callback from hook_menu()
 * add new taxonomy term for 'Company' which vocabulary is 5
 */
function otherterm_add_term_company() {
  $form_id = 'taxonomy_form_term';

  module_load_include('inc', 'taxonomy', 'taxonomy.admin');
  $vocabulary = taxonomy_vocabulary_load(5);

  $edit = array();
  $form = drupal_get_form($form_id, $edit, $vocabulary);

  /** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
  global $user;
  if (!in_array('administrator', $user->roles)) {
    $form['relations']['#attributes']['class'][] = 'element-hidden';
    $form['description']['format']['#access'] = FALSE;
  }

  $form['name']['#attributes']['placeholder'] = 'Company Name';
  $form['description']['value']['#attributes']['placeholder'] = 'Client Description';

  $form['field_company_bank_name']['und'][0]['value']['#attributes']['placeholder'] = 'Bank Name';
  $form['field_company_account_number']['und'][0]['value']['#attributes']['placeholder'] = 'Account Number';

  /** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */

  $output = drupal_render($form);

  return $output;
}