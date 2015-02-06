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
 * Implements hook_form(), callback from hook_menu()
 */
function useradmin_create_user_form($form, &$form_state) {
  $form['name'] = array(
    '#title' => 'username',
    '#description' => 'choose a username',
    '#type' => 'textfield',
    '#required' => TRUE,
    '#prefix' => '<div class="col-xs-10 col-sm-6 clear-both">',
    '#suffix' => '</div>',
  );
  $form['mail'] = array(
    '#title' => 'email',
    '#description' => 'enter a valid email address',
    '#type' => 'textfield',
    '#required' => TRUE,
    '#prefix' => '<div class="col-xs-10 col-sm-6 clear-both">',
    '#suffix' => '</div>',
    '#element_validate' => array('useradmin_validate_email'),
  );
  $form['roles'] = array(
    '#type' => 'checkboxes',
    '#options' => user_roles(TRUE, 'roles option for add user'),
    '#title' => t('User Roles'),
    '#prefix' => '<div class="col-xs-10 clear-both">',
    '#suffix' => '</div>',
  );
  $form['pass'] = array(
    '#type' => 'password_confirm', 
    '#prefix' => '<div class="col-xs-10 clear-both">',
    '#suffix' => '</div>',
    '#element_validate' => array('useradmin_validate_field_empty'),
  );
  /** - - - - - - - - - - - - - - - - - - - -  */
  // submit
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#prefix' => '<div class="col-xs-10 col-sm-6 text-center clear-both">',
    '#element_validate' => array('useradmin_validate_field_empty'),
  );
  $form['Cancel'] = array(
    '#type' => 'button',
    '#value' => t('Cancel'),
    '#attributes' => array('class' => array('btn-danger')),
    '#suffix' => '</div>',
  );
  /** - - - - - - - - - - - - - - - - - - - -  */
  return $form;
}

/**
 * Implements hook_form_submit()
 */
function useradmin_create_user_form_submit($form, &$form_state) {
  $mail = $form_state['values']['mail'];
  $username = $form_state['values']['name'];
  $roles = user_roles();
  $roles_array = '';
  foreach ($form_state['values']['roles'] as $key => $row) {
    // if checkbox is off, value is '0';
    if ($row > 0) {
      $roles_array[$key] = $roles[$key];
    }
  }
  /** - - - - - - - - - - - - - - - - - - - -  */
  $edit = array(
    'name' => $username,
    'pass' => $form_state['values']['pass'], // note: do not md5 the password
    'mail' => $mail,
    'status' => 1,
    'init' => $mail,
    'roles' => $roles,
  );
  user_save(NULL, $edit);
  /** - - - - - - - - - - - - - - - - - - - -  */
  watchdog('useradmin', 'New User - @name - created successfully', array('@name' => $username), WATCHDOG_NOTICE);
  drupal_set_message(t('The new User - @name- has been saved successfully.', array('@name' => $username)));
}

/**
 * call function valid_email_address() to valid email
 */
function useradmin_validate_email($element, &$form_state) {
  $value = $element['#value'];
  if (!valid_email_address($value)) {
    form_error($element, t('Please enter a valid email address.'));
  }
}

/**
 * 
 */
function useradmin_validate_field_empty($element, &$form_state) {
  $value = $element['#value'];
  if (empty($element['#value']) || ($element['#value'] == NULL)) {
    form_error($element, t('The field can not be empty.'));
  }
}