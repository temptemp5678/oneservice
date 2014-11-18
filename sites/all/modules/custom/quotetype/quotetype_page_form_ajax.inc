<?php
/** - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -  */
/**
 *
 */
function ajax_quotetype_select_company_name($form, &$form_state) {
  // Ajax framework commands
  $commands = array();

  $company_info = '';
  $company_name = '';
  
  // get selected value for "company_name"
  $company_name_vid = $form_state['values']['company_name'];
  
  if (isset($company_name_vid) && ($company_name_vid > 0)) {
    $term = taxonomy_term_load($company_name_vid);
    if ($term) {
      $company_name = $term->name;
      $company_info = $term->field_subcompany_bank_name['und'][0]['safe_value'];
    }
  }
  
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
  
  // Ajax commands
  if ($check_val) {
    $commands[] = ajax_command_invoke('.page-add-new-quotation .checkbox-authorize-stamp', 'removeClass', array('btn-warning'));
    $commands[] = ajax_command_invoke('.page-add-new-quotation .checkbox-authorize-stamp', 'addClass', array('btn-primary'));
    // $commands[] = ajax_command_invoke('.page-add-new-quotation .authorize-stamp-image', 'removeClass', array('element-invisible'));
    $commands[] = ajax_command_invoke('.authorize-stamp-image', 'removeClass', array('element-invisible'));
  }
  else {
    $commands[] = ajax_command_invoke('.page-add-new-quotation .checkbox-authorize-stamp', 'removeClass', array('btn-primary'));
    $commands[] = ajax_command_invoke('.page-add-new-quotation .checkbox-authorize-stamp', 'addClass', array('btn-warning'));
    $commands[] = ajax_command_invoke('.authorize-stamp-image', 'addClass', array('element-invisible'));
  }

  return array('#type' => 'ajax', '#commands' => $commands);
}
