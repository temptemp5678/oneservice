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
  $form_id = 'taxonomy_form_vocabulary';
  // $form_id = 'taxonomy_vocabulary_confirm_delete';
  
  module_load_include('inc', 'taxonomy', 'taxonomy.admin');
  $vocabulary = taxonomy_vocabulary_load(2);
  
  $edit = array();
  // $form = drupal_get_form($form_id, $edit, $vocabulary);
  $form = drupal_get_form($form_id, $edit, $vocabulary->vid);
  $form = drupal_get_form($form_id, $edit, (array)$vocabulary);
  $output = drupal_render($form);

  return $output;
  // return $form;
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
