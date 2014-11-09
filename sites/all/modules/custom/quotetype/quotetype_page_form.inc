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
  $form['top']['company_name'] = array(
    '#type' => 'select',
    '#title' => t('公司名称'),
    '#options' => drupal_map_assoc(array(t('北京万博信普公司'), t('北京万博一梦公司'))),
    '#prefix' => '<div class="col-xs-6 col-md-3 clear-both">',
    '#suffix' => '</div>',
    '#ajax' => array('callback' => 'ajax_quotetype_select_company_name', 'effect' => 'fade',),
  );
  $form['top']['warranty_day'] = array(
    '#type' => 'textfield',
    '#title' => t('保修长度'),
    '#default_value' => 180, 
    '#prefix' => '<div class="col-xs-1">',
    '#suffix' => '</div>',
    '#ajax' => array('callback' => 'ajax_quotetype_input_warranty_day', 'effect' => 'fade',),
  );
  $form['top']['apply_date'] = array(
    '#type' => 'date',
    '#title' => t('日期'),
    '#prefix' => '<div class="col-xs-4">',
    '#suffix' => '</div>',
    '#ajax' => array('callback' => 'ajax_quotetype_select_company_name'),
  );
  $form['top']['authorize_stamp'] = array(
    '#type' => 'checkbox',
    '#title' => t('授权'),
    '#prefix' => '<div class="col-xs-1"><div class="btn btn-warning checkbox-authorize-stamp">',
    '#suffix' => '</div></div>',
    '#ajax' => array('callback' => 'ajax_quotetype_check_authorize_stamp', 'effect' => 'fade',),
  );
  
  
  $form['quotation_title'] = array(
    '#type' => 'item',
    '#prefix' => '<div class="col-xs-5 col-xs-offset-2 clear-both">',
    '#suffix' => '</div>',
  );
  $form['quotation_markup_one'] = array(
    '#type' => 'item',
    '#markup' => t('产品保修期外维修单') . '<br />'
               . t('贵公司送修的解码器')
               . t('型号:') . '<br />'
               . '<p><span class="quotation_insert_markup_device_type">'
               . '</span></p>'
               . t('已经超过保修期, 需要更换配件, 维修后仅对该设备配件将提供为期')
               . '<span class="quotation_insert_markup_warranty_day">'
               .  180 
               . '</span>'
               . t('天的保修服务。')
               . '<br />'
               . t('维修情况如下：'),
    '#prefix' => '<div class="col-xs-10 col-xs-offset-2 clear-both">',
    '#suffix' => '</div>',
  );
  $form['quote_item'] = array(
    '#type' => 'item',
    '#markup' => '<p></p>',
    '#prefix' => '<div class="col-xs-10 col-xs-offset-2 quote-row-output-html color-449bb5 clear-both">',
    '#suffix' => '</div>',
  );
  
  $form['quotation_markup_eleven'] = array(
    '#type' => 'item',
    '#markup' => t('因已经超过保修期，需要支付维修费.费用为￥6900.00 (人民币陆仟玖佰元整)。维修后该设备相同部件将提供为期') 
               . '<span class="quotation_insert_markup_warranty_day">'
               .  180 
               . '</span>'
               . t('天的保修服务.')
               . '<br />'
               . t('以下是我司有关汇款信息：') . '<br /><br />'
               . '<span class="quotation_insert_markup_company_info">'
               . t('名称：北京万博信普通讯技术有限公司') . '<br />' 
               . t('开户行：交通银行北京水碓子支行') . '<br />'
               . t('帐号：110060970018010024476') 
               . '</span>'
               . '<br /><br />'
               . t('收到维修费后，')
               . '<span class="quotation_insert_markup_company_name">'
               . t('北京万博信普通讯技术有限公司')
               . '</span>'
               . t('负责开具发票，并将设备快递回贵公司。') . '<br />'
               . t('李靖'),
    '#prefix' => '<div class="col-xs-10 col-xs-offset-2 clear-both">',
    '#suffix' => '</div>',
  );
  
  $stamp_image_path = '/' . drupal_get_path('module', 'quotetype') . '/images/wanbo_quote_stamp.png';
  $stamp_image_variables = array(
                            'path' => $stamp_image_path,
                            'alt' => 'Stamp',
                            'title' => 'Stamp',
                            'width' => '128px',
                            'height' => '128px',
                           );
  $stamp_image = theme('image', $stamp_image_variables);
  $form['bottom']['text_three'] = array(
    '#type' => 'item',
    '#markup' => $stamp_image,
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
    '#prefix' => '<div class="estimate-page-submit-wrapper text-center clear-both">',
  );
  $form['Cancel'] = array(
    '#type' => 'submit',
    '#value' => t('Reset'),
    '#attributes' => array('class' => array('btn-danger'), 'onclick' => "javascript:location.href='../estimate-archives'"),
    '#suffix' => '</div>',
  );
  
  /** Embed a view from Views  - - - - - - - - - - - - - - - - - - - -  */
  $content = views_embed_view('repair_list_no_quote_yet');
  $form['attach']['views'] = array(
    '#type' => 'item',
    '#markup' => $content,
    '#prefix' => '<p></p><div class="col-xs-12 clear-both">',
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
  dpm($form_state);
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
  $node->field_quote_company_name[$node->language][0]['value'] = $form_state['values']['company_name'];

  // update field
  // field_attach_presave('node', $node);
  // field_attach_update('node', $node);

  // save node
  node_save($node);

  /** - - - - - - - - - - - - - - - - - - - -  */
  watchdog('quotetype', 'New Quote Node - @name - created successfully', array('@name' => $node->nid), WATCHDOG_NOTICE);
  drupal_set_message(t('The new Quote - @name- has been saved successfully.', array('@name' => $node->nid)));

  // redirect page
  $form_state['redirect'] = array('node/'. $node->nid);
}
