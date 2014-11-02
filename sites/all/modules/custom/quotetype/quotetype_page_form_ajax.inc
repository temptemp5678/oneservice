<?php
/** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
/**
 * Footing Section
 * footing dimension calculation
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
  }
  if else ($company_name_val == 1) {
    $company_info = t('名称：北京万博一梦有限公司') . '<br />' 
                  . t('开户行：工商银行加拿大团结湖支行') . '<br />'
                  . t('帐号：856624470018010924147');
  }
  
  $company_text = 'ajax_command_invoke';

  // Ajax commands
  $commands[] = ajax_command_invoke('.page-add-new-quotation #edit-text-one', 'text', array($company_info));
  $commands[] = ajax_command_html('.page-add-new-quotation #edit-text-two', array($company_info));

  return array('#type' => 'ajax', '#commands' => $commands);
}
