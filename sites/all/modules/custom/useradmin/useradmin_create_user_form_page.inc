<?php
/**
 * @file for Set default title of term
 */

/**
 *
 */
function useradmin_new_user_tt() {
  global $user;

  $form_id = 'user_profile_form';
  $form_id = 'user_register_form';


  $form_state = array();
  $form_state['build_info']['args'] = array($user);

  // Load user.pages.inc and ensure it is automatically reloaded if
  // this form is rebuilt via AJAX or other means.
  form_load_include($form_state, 'inc', 'user', 'user.pages');

  $form = drupal_build_form($form_id, $form_state);

  return $form;
}

/**
 * 
 */
function useradmin_new_user_access() {
  global $user;

  // set temporary permission for normal user
  $perm = &drupal_static('user_access');
  $perm[$user->uid]['administer users'] = TRUE;

  $form_id = 'user_register_form';

  $form = drupal_get_form($form_id);
  $output = drupal_render($form);

  // unset the permission
  unset($perm[$user->uid]['administer users']);

  return $output;
}
