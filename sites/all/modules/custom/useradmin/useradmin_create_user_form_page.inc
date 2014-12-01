<?php
/**
 * @file for Set default title of term
 */
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
    '#maxlength' => 64, 
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
    // '#element_validate' => array('useradmin_validate_field_empty'),
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
 * 
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
    drupal_set_message(t('User email of'). ' - ' . $value . ' - ' . t('is invalid'), 'error');
    form_error($element, t('Please enter a valid email address.'));
  }
}

/**
 * Implements hook_form_submit()
 */
function useradmin_create_user_form_submit($form, &$form_state) {
  $mail = $form_state['values']['mail'];
  $username = $form_state['values']['name'];
  // email_validate
  if (!valid_email_address($mail)) {
    drupal_set_message(t('User email of'). ' - ' . $username . ' - ' . t('is invalid'), 'error');
    return;
  }
  
  if (empty($form_state['values']['pass']) || ($form_state['values']['pass'])) {
    drupal_set_message(t('Password is invalid'), 'error');
    return;
  }
  
  $account = new StdClass();
  $account->is_new = TRUE;
  $account->status = TRUE;
  $account->name = $username;
  $account->pass = $form_state['values']['pass'];
  $account->mail = $form_state['values']['mail'];
  $account->init = $form_state['values']['mail'];
  $account->roles = $form_state['values']['roles'];

  user_save($account);

  /** - - - - - - - - - - - - - - - - - - - -  */
  watchdog('useradmin', 'New User - @name - created successfully', array('@name' => $username), WATCHDOG_NOTICE);
  drupal_set_message(t('The new User - @name- has been saved successfully.', array('@name' => $username)));
}