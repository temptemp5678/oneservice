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
  if ($company_name_val == 0) {
    $company_info = t('名称：北京万博信普通讯技术有限公司') . '<br />' 
                  . t('开户行：交通银行北京水碓子支行') . '<br />'
                  . t('帐号：110060970018010024476');
    $company_item_one = t('收到维修费后，北京万博信普通讯技术有限公司负责开具发票，并将设备快递回贵公司。');
  }
  else if ($company_name_val == 1) {
    $company_info = t('名称：北京万博一梦有限公司') . '<br />' 
                  . t('开户行：工商银行加拿大团结湖支行') . '<br />'
                  . t('帐号：856624470018010924147');
    $company_item_one = t('收到维修费后，北京万博一梦有限公司负责开具发票，并将设备快递回贵公司。');
  }
  
  $company_text = 'ajax_command_invoke';

  // Ajax commands
  // $commands[] = ajax_command_invoke('#edit-text-five', 'text', array($company_info));
  $commands[] = ajax_command_html('.page-add-new-quotation .text-two-wrapper div', $company_info);
  $commands[] = ajax_command_html('#edit-text-four', $company_item_one);
  
  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * 
 */
function ajax_quotetype_input_warranty_day($form, &$form_state) {
  // Ajax framework commands
  $commands = array();

  // get selected value for "warranty_day"
  $warranty_day_val = $form_state['values']['warranty_day'];
  
  // Ajax commands
  $commands[] = ajax_command_invoke('.page-add-new-quotation .quotation_markup_eleven_insert', 'text', array($warranty_day_val));
  
  return array('#type' => 'ajax', '#commands' => $commands);
}
