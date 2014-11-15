<?php
/**
 * @file for Add new term
 */
 
/**
 * Implements hook_form(), callback from hook_menu()
 */
function clientterm_add_new_term_form($form, &$form_state) {
  /** left - - - - - - - - - - - - - - - - - - - -  */
  $form['markup_leftone'] = array(
    '#type' => 'markup',
    '#prefix' => '<div class="col-xs-12 col-sm-6">',
  );
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('客户名称'),
    '#attributes' => array('placeholder' => 'Client Title'),
    '#prefix' => '<div class="col-xs-10">',
    '#suffix' => '</div>',
  );
  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('客户描述'),
    '#rows' => 2,
    '#attributes' => array('placeholder' => 'Client Description'),
    '#prefix' => '<div class="col-xs-10 clear-both">',
    '#suffix' => '</div>',
  );
  $form['client_province'] = array(
    '#type' => 'select',
    '#title' => t('所在省份'),
    '#options' => taxonomy_allowed_values(field_info_field('field_client_province')),
    '#prefix' => '<div class="col-xs-10 clear-both">',
    '#suffix' => '</div>',
  );
  $form['client_contactaddress'] = array(
    '#type' => 'textfield',
    '#title' => t('通讯地址'),
    '#attributes' => array('placeholder' => 'Client Address'),
    '#prefix' => '<div class="col-xs-10">',
    '#suffix' => '</div>',
  );
  $form['markup_lefttwo'] = array(
    '#type' => 'markup',
    '#suffix' => '</div>',
  );
  
  /** right - - - - - - - - - - - - - - - - - - - -  */
  $form['markup_rightone'] = array(
    '#type' => 'markup',
    '#prefix' => '<div class="col-xs-12 col-sm-6">',
  );
  $form['contact']['client_contactname'] = array(
    '#type' => 'textfield',
    '#title' => t('联系人'),
    '#attributes' => array('placeholder' => 'Name'),
    '#prefix' => '<div class="col-xs-12 col-sm-8">',
    '#suffix' => '</div>',
  );
  $form['contact']['client_contactphone'] = array(
    '#type' => 'textfield',
    '#title' => t('联系电话'),
    '#attributes' => array('placeholder' => 'Phone'),
    '#prefix' => '<div class="col-xs-12 col-sm-8">',
    '#suffix' => '</div>',
  );
  $form['contact']['client_contactemail'] = array(
    '#type' => 'textfield',
    '#title' => t('电子邮件'),
    '#attributes' => array('placeholder' => 'email'),
    '#prefix' => '<div class="col-xs-12 col-sm-8">',
    '#suffix' => '</div>',
  );
  $form['markup_righttwo'] = array(
    '#type' => 'markup',
    '#suffix' => '</div>',
  );
  /** right end - - - - - - - - - - - - - - - - - - - -  */

  /** - - - - - - - - - - - - - - - - - - - -  */
  // submit
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#prefix' => '<div class="add-new-term-page-submit-wrapper text-center clear-both">',
  );
  $form['Cancel'] = array(
    '#type' => 'button',
    '#value' => t('Cancel'),
    '#attributes' => array('class' => array('btn-danger')),
    '#suffix' => '</div>',
  );
dpm($form);
  /** - - - - - - - - - - - - - - - - - - - -  */
  return $form;
}

/**
 * Implements hook_form_submit()
 */
function clientterm_add_new_term_form_submit($form, &$form_state) {
  // The VID of "Client" vocabulary is 2
  $vid = 2;
  $name = $form_state['values']['name'];

  /** - - - - - - - - - - - - - - - - - - - -  */
  // create a taxonomy term
  $term = new stdClass();
  $term->name = $name;
  $term->description = $form_state['values']['description'];
  $term->vid = $vid;
  
  // optional field
  $term->field_client_province[LANGUAGE_NONE][0]['tid'] = $form_state['values']['client_province'];
  $term->field_client_contactaddress[LANGUAGE_NONE][0]['value'] = $form_state['values']['client_contactaddress'];
  $term->field_client_contactname[LANGUAGE_NONE][0]['value'] = $form_state['values']['client_contactname'];
  $term->field_client_contactphone[LANGUAGE_NONE][0]['value'] = $form_state['values']['client_contactphone'];
  $term->field_client_contactemail[LANGUAGE_NONE][0]['value'] = $form_state['values']['client_contactemail'];
  // save new term
  taxonomy_term_save($term);

  /** - - - - - - - - - - - - - - - - - - - -  */
  watchdog('clientterm', 'New Cilent - @name - created successfully', array('@name' => $name), WATCHDOG_NOTICE);
  drupal_set_message(t('The new Cilent - @name- has been saved successfully.', array('@name' => $name)));

  // redirect page
  // $form_state['redirect'] = array('home');
}
