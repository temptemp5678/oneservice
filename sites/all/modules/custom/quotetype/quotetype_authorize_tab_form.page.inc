<?php
/**
 * @file for Add new term
 */

/**
 * callback from hook_menu()
 * add "Authorize" tab on Quote node page
 */
function quotetype_authorize_tab_form($nid = NULL) {
  $node = node_load($nid);
  
  $stamp_value = 0;
  $stamp_class = 'btn-warning';
  if ($node->field_quote_authorize_stamp['und'][0]['value']) {
    $stamp_value = 1;
    $stamp_class = 'btn-primary';
  }
  
  $form['markup_emppty'] = array(
    '#type' => 'markup',
    '#markup' => '',
  );
  // only show on node page, not show on delete page
  if ((arg(0) == 'node') && is_numeric(arg(1)) && (arg(2) != 'delete')) {
    $form['authorize_stamp'] = array(
      '#type' => 'checkbox',
      '#title' => t('Authorize'),
      '#default_value' => $stamp_value,
      '#prefix' => '<div class="col-xs-2"><div class="btn ' . $stamp_class . ' checkbox-authorize-stamp">',
      '#suffix' => '</div></div>',
      '#ajax' => array('callback' => 'quotetype_ajax_stamp_callback', 'effect' => 'fade',),
    );
  }
  
  // submit button
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#prefix' => '<div class="estimate-page-submit-wrapper text-center clear-both">',
  );

  $form['Cancel'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel'),
    '#attributes' => array('class' => array('btn-danger'), 'onclick' => "javascript:location.href='../estimate-archives'"),
    '#submit' => array('_quotetype_authorize_tab_summit_cancel'),
  );
  return $form;
}


/**
 * Implements hook_form_submit()
 */
function quotetype_authorize_tab_form_submit($form, &$form_state) {
  $node->field_estimate_quote_client[$node->language][0]['tid'] = $form_state['values']['quote_client'];
}

/**
 * redirect page
 */
function _quotetype_authorize_tab_summit_cancel() {
  drupal_goto('quote-list');
}