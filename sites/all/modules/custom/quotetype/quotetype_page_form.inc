<?php
/**
 * @file for New Quotation Form
 */

/**
 * Implements hook_form(), callback from hook_menu()
 */
function quotetype_add_quote_form($form, &$form_state) {
  if (!isset($account)) {
    $account = $GLOBALS['user'];
  }

  /** form - - - - - - - - - - - - - - - - - - - -  */
  $form['foot'] = array(
    '#type' => 'item',
    '#markup' => t('Quantity'),
    '#prefix' => '<div class="col-xs-1 col-xs-offset-2 clear-both">',
    '#suffix' => '</div>',
  );

  /** return form - - - - - - - - - - - - - - - - - - - -  */
  return $form;
}

/**
 * redirect page
 */
function quotetype_callback_summit_cancel() {
  drupal_goto('estimate-archives');
}

/**
 * Implements hook_form_submit()
 */
function quotetype_add_quote_form_submit($form, &$form_state) {
}