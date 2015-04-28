<?php
/**
 * @file for Add new term
 */

/**
 * callback from hook_menu()
 * add "Authorize" tab on Quote node page
 */
function quotetype_authorize_tab_form($form, &$form_state, $nid = NULL) {
  // only show on node page, not show on delete page
  if (!(arg(0) == 'node') && is_numeric(arg(1)) && (arg(2) != 'delete')) {
    return;
  }

  $node = node_load($nid);
  if (!$node) {
    return;
  }
  
  $stamp_value = 0;
  $stamp_class = 'btn-warning';
  if (!empty($node->field_quote_authorize_stamp['und'][0]['value'])) {
    $stamp_class = 'btn-primary';
  }

  $form['authorize_button'] = array(
    '#type' => 'checkbox',
    '#title' => t('Authorize'),
    '#default_value' => $node->field_quote_authorize_stamp['und'][0]['value'],
    '#prefix' => '<div class="row"><div class="btn ' . $stamp_class . ' checkbox-authorize-stamp">',
    '#suffix' => '</div></div>',
  );

  // Authorize Stamp Image
  $QuoteInfo = new QuoteInfo($nid);
  $company_term_tid = $QuoteInfo->companyNameTid();
  
  $CompanyTermInfo = new CompanyTermInfo($company_term_tid);
  $stamp_image = $CompanyTermInfo->authorizeStampImage();
  $form['authorize_stamp'] = array(
    '#type' => 'item',
    '#markup' => '<div class="row text-center margin-top-24">' . $stamp_image . '</div>',
    '#states' => array(
      'visible' => array(
        ':input[name="authorize_button"]' => array('checked' => TRUE),
      ),
    ),
  );

  $form['row_place_holder'] = array(
    '#type' => 'item',
    '#markup' => '<div class="row text-center min-heigth-152"></div>',
    '#states' => array(
      'invisible' => array(
        ':input[name="authorize_button"]' => array('checked' => TRUE),
      ),
    ),
  );
  $form['pass_nid'] = array(
    '#type' => 'value',
    '#value' => $node->nid,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#prefix' => '<div class="estimate-page-submit-wrapper text-center clear-both">',
  );

  $form['Cancel'] = array(
    '#type' => 'submit',
    '#value' => t('Cancel'),
    '#attributes' => array('class' => array('btn-danger'), 'onclick' => 'javascript:location.href="node/' . $node->nid . '"'),
    '#submit' => array('_quotetype_authorize_tab_summit_cancel'),
  );
  return $form;
}

/**
 * Implements hook_form_submit()
 */
function quotetype_authorize_tab_form_submit($form, &$form_state) {
  $nid = $form_state['values']['pass_nid'];
  $node = node_load($nid);
  if (isset($node)) {
    $field_language = field_language('node', $node, 'field_quote_client_name');
    $node->field_quote_authorize_stamp[$field_language][0]['value'] = $form_state['values']['authorize_button'];
    // It's good to call field_attach_presave() too
    field_attach_presave('node', $node);
    field_attach_update('node', $node);
    
    $form_state['redirect'] = 'node/' . $nid;
  }
}

/**
 * redirect page
 */
function _quotetype_authorize_tab_summit_cancel() {
  drupal_goto('quote-list');
}