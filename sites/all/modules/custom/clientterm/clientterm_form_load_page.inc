<?php
/**
 * @file for Add new term
 */

/**
 * Implements hook_form(), callback from hook_menu()
 */
function clientterm_form_load_user() {
  global $user;
  $form_id = 'user_profile_form';
  $form_state = array();
  $form_state['build_info']['args'] = array($user);

  // Load user.pages.inc and ensure it is automatically reloaded if
  // this form is rebuilt via AJAX or other means.
  form_load_include($form_state, 'inc', 'user', 'user.pages');

  $form = drupal_build_form($form_id, $form_state);
  return $form;

}

/**
 * Implements hook_form(), callback from hook_menu()
 */
function clientterm_form_load_term() {
  $form_id = 'taxonomy_form_term';

  module_load_include('inc', 'taxonomy', 'taxonomy.admin');
  $vocabulary = taxonomy_vocabulary_load(2);

  $edit = array();
  $form = drupal_get_form($form_id, $edit, $vocabulary);
  
  dpm($form);
  global $user;
  if (!in_array('administrator', $user->roles)) {
  }

  // $form['description']['#access'] = FALSE;
  // $form['relations']['#access'] = FALSE;

  $form['name']['#prefix'] = '<div class="col-sm-6">';
  $form['name']['#suffix'] = '</div>';

  $form['field_client_contactname']['#prefix'] = '<div class="col-sm-6">';
  $form['field_client_contactname']['#suffix'] = '</div>';

  $form['field_client_contactphone']['#prefix'] = '<div class="col-sm-6">';
  $form['field_client_contactphone']['#suffix'] = '</div>';

  $form['field_client_contactemail']['#prefix'] = '<div class="col-sm-6">';
  $form['field_client_contactemail']['#suffix'] = '</div>';

  $form['field_client_province']['#prefix'] = '<div class="col-sm-6">';
  $form['field_client_province']['#suffix'] = '</div>';

  $form['field_client_contactaddress']['#prefix'] = '<div class="col-sm-6">';
  $form['field_client_contactaddress']['#suffix'] = '</div>';

  $form['field_client_clienttype']['#prefix'] = '<div class="col-sm-6">';
  $form['field_client_clienttype']['#suffix'] = '</div>';

  $form['actions']['submit']['#prefix'] = '<div class="col-sm-12">';
  $form['actions']['submit']['#suffix'] = '</div>';

  $form['actions']['submit']['#attributes']['class'][] = 'clear-both';
  $form['actions']['submit']['#attributes']['class'][] = 'float-left';

  $output = drupal_render($form);

  return $output;
}

/**
 * Implements hook_form(), callback from hook_menu()
 */
function clientterm_form_load_vocabulary() {
  $form_id = 'taxonomy_form_vocabulary';

  $form = drupal_get_form($form_id);
  $output = drupal_render($form);

  return $output;
}
