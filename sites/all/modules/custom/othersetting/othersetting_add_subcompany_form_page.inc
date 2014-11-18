<?php
/**
 * @file for Set default title of term
 */
/**
 * Implements hook_form(), callback from hook_menu()
 */
function othersetting_add_subcompany_form($form, &$form_state) {
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('子公司名称'),
    '#attributes' => array('placeholder' => 'SubCompany'),
    '#prefix' => '<div class="col-xs-10 col-sm-6">',
    '#suffix' => '</div>',
  );
  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('描述'),
    '#rows' => 2,
    '#attributes' => array('placeholder' => 'Description'),
    '#prefix' => '<div class="col-xs-10 col-sm-6 clear-both">',
    '#suffix' => '</div>',
  );
  $form['bank_name'] = array(
    '#type' => 'textfield',
    '#title' => t('开户行'),
    '#attributes' => array('placeholder' => 'Bank Name'),
    '#prefix' => '<div class="col-xs-10 col-sm-6 clear-both">',
    '#suffix' => '</div>',
  );
  $form['account_number'] = array(
    '#type' => 'textfield',
    '#title' => t('银行帐号'),
    '#attributes' => array('placeholder' => 'Account Number'),
    '#prefix' => '<div class="col-xs-10 col-sm-6 clear-both">',
    '#suffix' => '</div>',
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
function othersetting_add_subcompany_form_submit($form, &$form_state) {
  // The VID of "SubCompany" vocabulary is 5
  $vid = 5;
  $name = $form_state['values']['name'];

  /** - - - - - - - - - - - - - - - - - - - -  */
  // create a taxonomy term
  $term = new stdClass();
  $term->name = $name;
  $term->description = $form_state['values']['description'];
  $term->vid = $vid;
  
  // optional field
  $term->field_subcompany_bank_name[LANGUAGE_NONE][0]['value'] = $form_state['values']['bank_name'];
  $term->field_subcompany_account_number[LANGUAGE_NONE][0]['value'] = $form_state['values']['account_number'];
  // save new term
  taxonomy_term_save($term);

  /** - - - - - - - - - - - - - - - - - - - -  */
  watchdog('subcompany', 'New SubCompany - @name - created successfully', array('@name' => $name), WATCHDOG_NOTICE);
  drupal_set_message(t('The new SubCompany - @name- has been saved successfully.', array('@name' => $name)));
}