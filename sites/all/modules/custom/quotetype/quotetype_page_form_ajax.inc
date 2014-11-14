<?php
/** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
/**
 *
 */
function ajax_quotetype_select_company_name($form, &$form_state) {
  // Ajax framework commands
  $commands = array();

  // get selected value for "company_name"
  $company_name_val = $form_state['values']['company_name'];
  if ($company_name_val == '北京万博信普公司') {
    $company_info = t('名称：北京万博信普通讯技术有限公司') . '<br />' 
                  . t('开户行：交通银行北京水碓子支行') . '<br />'
                  . t('帐号：110060970018010024476');
    $company_name = t('北京万博信普通讯技术有限公司');
  }
  else if ($company_name_val == '北京万博一梦公司') {
    $company_info = t('名称：北京万博一梦有限公司') . '<br />' 
                  . t('开户行：工商银行加拿大团结湖支行') . '<br />'
                  . t('帐号：856624470018010924147');
    $company_name = t('北京万博一梦有限公司');
  }
  
  $company_text = 'ajax_command_invoke';

  // Ajax commands
  // $commands[] = ajax_command_invoke('#edit-text-five', 'text', array($company_info));
  $commands[] = ajax_command_html('.page-add-new-quotation .quotation_insert_markup_company_info', $company_info);
  $commands[] = ajax_command_invoke('.page-add-new-quotation .quotation_insert_markup_company_name', 'text', array($company_name));
  
  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * 
 */
function ajax_quotetype_input_sum_price($form, &$form_state) {
  // Ajax framework commands
  $commands = array();

  // get input value for "sum-price"
  $input_amount = round($form_state['values']['sum_price'], 2);
  $basic_amount = round($form_state['values']['basic_price'], 2);
  $dicount_amount = round(($input_amount - $basic_amount),2);
  $chinese_amount = num2rmb($input_amount);
  
  // Ajax commands
  $commands[] = ajax_command_invoke('.page-add-new-quotation .quotation-js-insert-final-discount', 'text', array($dicount_amount));
  $commands[] = ajax_command_invoke('.page-add-new-quotation .quotation-insert-markup-sum-price', 'text', array($input_amount));
  $commands[] = ajax_command_invoke('.page-add-new-quotation .quotation-insert-markup-chinese-price', 'text', array($chinese_amount));
  
  return array('#type' => 'ajax', '#commands' => $commands);
}
/**
 * 
 */
function ajax_quotetype_input_warranty_day($form, &$form_state) {
  // Ajax framework commands
  $commands = array();

  // get input value for "warranty_day"
  $warranty_day_val = $form_state['values']['warranty_day'];
  
  // Ajax commands
  $commands[] = ajax_command_invoke('.page-add-new-quotation .quotation_insert_markup_warranty_day', 'text', array($warranty_day_val));
  
  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * 
 */
function ajax_quotetype_select_create_date($form, &$form_state) {
  // Ajax framework commands
  $commands = array();

  // get selected value for "create_date"
  $create_date_val = $form_state['values']['create_date'];
  
  // Ajax commands
  $commands[] = ajax_command_invoke('.page-add-new-quotation .quotation_insert_markup_create_date', 'text', array($create_date_val));
  
  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * 
 */
function ajax_quotetype_check_authorize_stamp($form, &$form_state) {
  // Ajax framework commands
  $commands = array();

  // get check value, 1 for true, 0 for false
  $check_val = $form_state['values']['authorize_stamp'];
  
  // if ($check_val) {
  if ($check_val) {
    $commands[] = ajax_command_invoke('.page-add-new-quotation .checkbox-authorize-stamp', 'removeClass', array('btn-warning'));
    $commands[] = ajax_command_invoke('.page-add-new-quotation .checkbox-authorize-stamp', 'addClass', array('btn-primary'));
    $commands[] = ajax_command_invoke('.page-add-new-quotation .authorize-stamp-image', 'removeClass', array('element-invisible'));
  }
  else {
    $commands[] = ajax_command_invoke('.page-add-new-quotation .checkbox-authorize-stamp', 'removeClass', array('btn-primary'));
    $commands[] = ajax_command_invoke('.page-add-new-quotation .checkbox-authorize-stamp', 'addClass', array('btn-warning'));
    $commands[] = ajax_command_invoke('.page-add-new-quotation .authorize-stamp-image', 'addClass', array('element-invisible'));
  }
  // Ajax commands
  
  return array('#type' => 'ajax', '#commands' => $commands);
}
