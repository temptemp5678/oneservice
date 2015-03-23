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
  // Because we have many fields with the same values, we have to set
  // #tree to be able to access them.
  $form['nid']['#tree'] = TRUE;
  for ($f = 0; $f < 10; $f++) {
    $form['nid'][$f]['repair_nid'] = array(
      '#type' => 'textfield',
      '#attributes' => array('class' => array('addmore-select-repair-nid', $f, 'element-invisible')),
      '#prefix' => '<div class="col-xs-1 quotation-js-insert-repair-nid element-invisible">',
      '#suffix' => '</div>',
      '#element_validate' => array('element_estimate_integer_validate'),
    );
  }
  
  $company_name_option = taxonomy_allowed_values(field_info_field('field_quote_company_name'));
  $form['top']['company_name'] = array(
    '#type' => 'select',
    '#title' => t('本公司'),
    '#options' => $company_name_option,
    '#default_value' => variable_get('quote_default_value_company_name', ''),
    '#prefix' => '<div class="col-xs-6 col-md-3 clear-both">',
    '#suffix' => '</div>',
    '#ajax' => array('callback' => 'ajax_quotetype_select_company_name', 'effect' => 'fade',),
  );
  $form['top']['client_name'] = array(
    '#type' => 'textfield',
    '#title' => t('客户名称'),
    '#prefix' => '<div class="col-xs-6 col-md-3">',
    '#suffix' => '</div>',
  );
  $form['top']['sum_price'] = array(
    '#type' => 'textfield',
    '#title' => t('总价'),
    '#prefix' => '<div class="col-xs-4 col-md-2">',
    '#suffix' => '</div>',
    '#ajax' => array('callback' => 'ajax_quotetype_input_sum_price', 'effect' => 'fade',),
  );
  // hide, just for AJAX usage
  $form['top']['basic_price'] = array(
    '#type' => 'textfield',
    '#attributes' => array('class' => array('element-invisible')),
    '#prefix' => '<div class="col-xs-1 element-invisible">',
    '#suffix' => '</div>',
  );
  
  $form['top']['warranty_day'] = array(
    '#type' => 'textfield',
    '#title' => t('保修'),
    '#default_value' => variable_get('quote_default_value_warranty_day'), 
    '#prefix' => '<div class="col-xs-4 col-md-2">',
    '#suffix' => '</div>',
    '#element_validate' => array('element_estimate_decimal_validate'),
    '#ajax' => array('callback' => 'ajax_quotetype_input_warranty_day', 'effect' => 'fade',),
  );
  $form['top']['create_date'] = array(
    '#type' => 'date_popup',
    '#title' => t('日期'),
    '#default_value' => date('Y-m-d'),
    '#date_format' => 'Y-m-d',
    '#date_label_position' => 'within',
    '#attributes' => array('placeholder' => 'Date'),
    '#prefix' => '<div class="col-xs-4 col-md-2">',
    '#suffix' => '</div>',
    '#ajax' => array('callback' => 'ajax_quotetype_select_create_date', 'event' => 'change'),
  );
  
  if (user_access('permission for moderator role', $account)) {
    $form['top']['authorize_stamp'] = array(
      '#type' => 'checkbox',
      '#title' => t('授权'),
      '#prefix' => '<div class="col-xs-2 clear-both"><div class="btn btn-warning checkbox-authorize-stamp">',
      '#suffix' => '</div></div>',
      '#ajax' => array('callback' => 'ajax_quotetype_check_authorize_stamp', 'effect' => 'fade',),
    );
  }
  
  $form['quotation_title'] = array(
    '#type' => 'item',
    '#prefix' => '<div class="col-xs-5 col-xs-offset-2 clear-both">',
    '#suffix' => '</div>',
  );
  $form['quotation_markup_one'] = array(
    '#type' => 'item',
    '#markup' => othersetting_quote_page_content(),
    '#prefix' => '<div class="col-xs-10 col-xs-offset-2 clear-both">',
    '#suffix' => '</div>',
  );
  
  // Authorize Stamp Image
  $company_selected = isset($form_state['values']['company_name']) ? $form_state['values']['company_name'] : key($company_name_option);
  $CompanyTermInfo = new CompanyTermInfo($company_selected);
  $company_stamp_image = $CompanyTermInfo->authorizeStampImage();
  $form['bottom']['text_three'] = array(
    '#type' => 'item',
    '#markup' => $company_stamp_image,
    '#prefix' => '<div class="col-xs-12 authorize-stamp-image text-right element-invisible clear-both">',
    '#suffix' => '</div>',
  );
  $form['bottom']['text_five'] = array(
    '#type' => 'item',
    '#prefix' => '<div class="col-xs-10 col-xs-offset-2 clear-both">',
    '#suffix' => '</div>',
  );
  
  /** submit button - - - - - - - - - - - - - - - - - - - -  */
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
    '#attributes' => array('class' => array('disabled')),
    '#prefix' => '<div class="add-repair-page-submit-wrapper text-center clear-both">',
  );
  $form['Cancel'] = array(
    '#type' => 'button',
    '#value' => t('Reset'),
    '#attributes' => array('class' => array('btn-danger'), 'onclick' => "javascript:location.href='../add_new_quotation'"),
    '#suffix' => '</div>',
  );
  
  /**  - - - - - - - - - - - - - - - - - - - -  */
  $output = quotetype_tableselect_content_callback();
  $header = $output['header'];
  $options = $output['options'];
  
  $form['tableselect_nid'] = array(
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('No Repair item content available.'),
    '#js_select' => FALSE,
    // '#ajax' => array('callback' => 'quotetype_ajax_input_tableselect',),
    // Disable to call '#ajax' directly, Using '#process' to call a Bridge CallBack instead
    '#process' => array('form_process_tableselect', 'quotetype_tableselect_bridge_process_callback'),
  );

  /** return form - - - - - - - - - - - - - - - - - - - -  */
  return $form;
}

/**
 * redirect page
 */
function quotetype_callback_summit_cancel() {
  // drupal_goto('estimate-archives');
}

/**
 * Implements hook_form_submit()
 */
function quotetype_add_quote_form_submit($form, &$form_state) {
  // global $user;
  if (!isset($account)) {
    $account = $GLOBALS['user'];
  }
  /** - - - - - - - - - - - - - - - - - - - -  */
  // create new node
  $node = new stdClass();
  $node->type = 'quote';

  // The node_object_prepare() function provides the default values for the status, promote, sticky, and revision flags.
  node_object_prepare($node);

  $node->status = 1;
  $node->uid = $account->uid;
  $node->title = 'New Quote';
  $node->promote = 1;
  $node->created = time();;
  $node->timestamp = time();;
  $node->sticky = 0;
  $node->language = LANGUAGE_NONE;   // und
  $node->revision = 0;
  
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // format date value
  $date_value = time();
  if (isset($form_state['values']['create_date'])) {
    $date_value = strtotime($form_state['values']['create_date']);
  }
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  // save repair_nid
  for ($f = 0; $f < 10; $f++) {
    // add "(int)", transform "NULL value" to 0 for field value saving
    if ($form_state['values']['nid'][$f]['repair_nid']) {
      $node->field_quote_repair_nid[$node->language][$f]['value'] = (int) $form_state['values']['nid'][$f]['repair_nid'];
    }
  }
  // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
  $node->field_quote_company_name[$node->language][0]['tid'] = $form_state['values']['company_name'];
  $node->field_quote_client_name[$node->language][0]['value'] = $form_state['values']['client_name'];
  $node->field_quote_sum_price[$node->language][0]['value'] = $form_state['values']['sum_price'];
  $node->field_quote_warranty_day[$node->language][0]['value'] = $form_state['values']['warranty_day'];
  $node->field_quote_create_date[$node->language][0]['value'] = $date_value;
  $node->field_quote_authorize_stamp[$node->language][0]['value'] = $form_state['values']['authorize_stamp'];
  
  // save node
  node_save($node);
  
  /** - - - - - - - - - - - - - - - - - - - -  */
  // update field for Repair node
  // update "Quote Status Field of Repair Node" as "Yes" of value
  for ($f = 0; $f < 10; $f++) {
    $repair_nid = $form_state['values']['nid'][$f]['repair_nid'];
    if ($repair_nid > 0) {
      $repair_node = node_load($repair_nid, NULL, TRUE);
      if (isset($repair_node)) {
        $field_language = field_language('node', $repair_node, 'field_repair_quote_status');
        $repair_node->field_repair_quote_status[$field_language][0]['value'] = 1;
        // field_attach_presave('node', $repair_node);
        field_attach_update('node', $repair_node);
      }
    }
  }
  
  /** - - - - - - - - - - - - - - - - - - - -  */
  watchdog('quotetype', 'New Quote Node - @name - created successfully', array('@name' => $node->nid), WATCHDOG_NOTICE);
  drupal_set_message(t('The new Quote - @name- has been saved successfully.', array('@name' => $node->nid)));

  // redirect page
  $form_state['redirect'] = array('node/'. $node->nid);
}

/**
 * check string is valid decimal or not
 */
function element_estimate_decimal_validate($element, &$form_state) {
  if(!is_numeric($element['#value']) && !empty($element['#value'])) {
    form_error($element, t('You must input a number.'));
  }
}

/**
 * check string is valid integer or not
 */
function element_estimate_integer_validate($element, &$form_state) {
  $check_integer = '';
  $check_integer = (intval( $element['#value'] ) == $element['#value']);
  if( !empty($element['#value']) && (!is_numeric($element['#value'])) ) {
    form_error($element, t('You must input a number.'));
  }

  if( !empty($element['#value']) && is_numeric($element['#value']) && (intval( $element['#value'] ) != $element['#value']) ) {
    form_error($element, t('You must input a integer number.'));
  }
}