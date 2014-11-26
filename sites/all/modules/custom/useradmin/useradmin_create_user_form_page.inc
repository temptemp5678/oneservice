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
  );
  $form['mail'] = array(
    '#title' => 'email',
    '#description' => 'enter a valid email address',
    '#type' => 'textfield',
    '#required' => TRUE,
  );

  /** - - - - - - - - - - - - - - - - - - - -  */
  // submit
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#prefix' => '<div class="col-xs-10 col-sm-6 text-center clear-both">',
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
  $account = new StdClass();
  $account->is_new = TRUE;
  $account->status = TRUE;
  $account->name = $form_state['values']['name'];
  $account->pass = user_hash_password('somepassword');
  $account->mail = $form_state['values']['mail'];
  $account->init = $form_state['values']['mail'];
  $account->roles[5] = 'some role';
  $account->field_last_name[LANGUAGE_NONE][0]['value'] = 'some last name';
  user_save($account);

  /** - - - - - - - - - - - - - - - - - - - -  */
  watchdog('othersetting', 'New Company - @name - created successfully', array('@name' => $name), WATCHDOG_NOTICE);
  drupal_set_message(t('The new Company - @name- has been saved successfully.', array('@name' => $name)));
}