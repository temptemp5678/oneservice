<?php
/**
 * @file for Add new term
 */
 
/**
 * Implements hook_form(), callback from hook_menu()
 */
function deviceterm_add_new_term_form($form, &$form_state) {
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('设备名称'),
    '#attributes' => array('placeholder' => 'Client Title'),
    '#prefix' => '<div class="col-xs-10 col-md-6">',
    '#suffix' => '</div>',
  );
  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('设备描述'),
    '#rows' => 2,
    '#attributes' => array('placeholder' => 'Client Description'),
    '#prefix' => '<div class="col-xs-10 col-md-6 clear-both">',
    '#suffix' => '</div>',
  );
  /** - - - - - - - - - - - - - - - - - - - -  */
  // submit
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#prefix' => '<div class="col-xs-10 col-md-6 add-new-term-page-submit-wrapper text-center clear-both">',
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
function deviceterm_add_new_term_form_submit($form, &$form_state) {
  // The VID of "Device" vocabulary is 3
  $vid = 3;
  $name = $form_state['values']['name'];

  /** - - - - - - - - - - - - - - - - - - - -  */
  // create a taxonomy term
  $term = new stdClass();
  $term->name = $name;
  $term->description = $form_state['values']['description'];
  $term->vid = $vid;
  
  // save new term
  taxonomy_term_save($term);

  /** - - - - - - - - - - - - - - - - - - - -  */
  watchdog('deviceterm', 'New Device - @name - created successfully', array('@name' => $name), WATCHDOG_NOTICE);
  drupal_set_message(t('The new Device - @name- has been saved successfully.', array('@name' => $name)));

  // redirect page
  $form_state['redirect'] = array('device-list');
}
