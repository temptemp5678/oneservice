<?php
/**
 * @file for Add new term
 */
 
/**
 * Implements hook_form(), callback from hook_menu()
 */
function clientterm_add_new_term_form($form, &$form_state) {
  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Client Title'),
    '#attributes' => array('placeholder' => 'Client Title'),
    '#prefix' => '<div class="col-xs-12">',
    '#suffix' => '</div>',
  );
  $form['description'] = array(
    '#type' => 'textarea',
    '#title' => t('Client Description'),
    '#rows' => 2,
    '#attributes' => array('placeholder' => 'Client Description'),
    '#prefix' => '<div class="col-xs-12">',
    '#suffix' => '</div>',
  );
  
  /** - - - - - - - - - - - - - - - - - - - -  */
  // submit
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#prefix' => '<div class="add-new-term-page-submit-wrapper text-center">',
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
  
  // save new term
  taxonomy_term_save($term);

  /** - - - - - - - - - - - - - - - - - - - -  */
  watchdog('clientterm', 'New Cilent - @name - created successfully', array('@name' => $name), WATCHDOG_NOTICE);
  drupal_set_message(t('The new Cilent - @name- has been saved successfully.', array('@name' => $name)));

  // redirect page
  // $form_state['redirect'] = array('home');
}
