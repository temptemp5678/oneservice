<?php
/**
 * @file for Add new term
 */
 
/**
 * Implements hook_form(), callback from hook_menu()
 */
function clientterm_form_load_page() {
global $user;
  /** left - - - - - - - - - - - - - - - - - - - -  */
  $output = '33';
$form_id = 'user_profile_form';
$form_state = array();
$form_state['build_info']['args'] = array($user);

// Load user.pages.inc and ensure it is automatically reloaded if
// this form is rebuilt via AJAX or other means.
form_load_include($form_state, 'inc', 'user', 'user.pages');

$form = drupal_build_form($form_id, $form_state);
  return $form;
  
}