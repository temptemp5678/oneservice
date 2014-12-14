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
    '#title' => '+ ' . t('Quotation Default Value Setting'),
    '#collapsible' => TRUE,
    '#collapsible' => FALSE,
    '#collapsed' => TRUE,
    '#collapsed' => FALSE,
    '#attributes' => array('class' => array('programterm-default-title-page-wrapper')),
  );
  $form['quote_value']['quote_default_value_warranty_day'] = array(
    '#type' => 'textfield',
    '#title' => t('Warranty Day') . ' (' .  t('Days') . ')',
    '#attributes' => array('class' => array('quote-default-value-warranty-day-wrapper'), 'placeholder' => 'Warranty Day', 'pattern' => "\d*"),
    '#default_value' => variable_get('quote_default_value_warranty_day'),
    '#prefix' => '<div class="col-xs-6 col-md-2">',
    '#suffix' => '</div>',
  );
  $form['quote_value']['quote_default_value_company_name'] = array(
    '#type' => 'select',
    '#title' => t('Default Company'),
    '#options' => taxonomy_allowed_values(field_info_field('field_quote_company_name')),
    '#default_value' => variable_get('quote_default_value_company_name', ''),
    '#prefix' => '<div class="col-xs-10 col-md-4 clear-both">',
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
