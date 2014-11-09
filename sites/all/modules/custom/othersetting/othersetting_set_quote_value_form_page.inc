<?php
/**
 * @file for Set default title of term
 */

/**
 * Implements hook_form(), callback from hook_menu()
 */
function othersetting_set_quote_value_form($form, &$form_state) {
  if (!isset($account)) {
    $account = $GLOBALS['user'];
  }
  /** ---------------------------------------------------------------------------------------------- */

  /** - - - fieldset - - - */
  $form['quote_value'] = array(
    '#type' => 'fieldset',
    '#title' => '+ ' . t('Quotation Value'),
    '#collapsible' => TRUE,
    '#collapsible' => FALSE,
    '#collapsed' => TRUE,
    '#collapsed' => FALSE,
    '#attributes' => array('class' => array('programterm-default-title-page-wrapper')),
  );
  $form['quote_value']['quote_default_value_warranty_day'] = array(
    '#type' => 'textfield',
    '#title' => t('Warranty Day'),
    '#attributes' => array('class' => array('quote-default-value-warranty-day-wrapper'), 'placeholder' => 'Warranty Day', 'pattern' => "\d*"),
    '#default_value' => variable_get('quote_default_value_warranty_day'),
    '#prefix' => '<div class="col-xs-12">',
    '#suffix' => '</div>',
  );
  $form['quote_value']['quote_default_value_company_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Company Name'),
    '#attributes' => array('class' => array('quote-default-value-company-name-wrapper'), 'placeholder' => 'Company Name'),
    '#default_value' => variable_get('quote_default_value_company_name'),
    '#prefix' => '<div class="col-xs-12">',
    '#suffix' => '</div>',
  );

  /** - - - - - - - - - - - - - - - - - - - -  */
  // submit
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#prefix' => '<div class="othersetting-set-quote-value-form-page-submit-wrapper text-center">',
  );
  $form['Cancel'] = array(
    '#type' => 'button',
    '#value' => t('Cancel'),
    '#attributes' => array('class' => array('btn-danger')),
    '#suffix' => '</div>',
  );

  /** ---------------------------------------------------------------------------------------------- */
  // return $form;
  return system_settings_form($form);
}
