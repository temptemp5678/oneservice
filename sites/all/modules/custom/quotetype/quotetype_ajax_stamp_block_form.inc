<?php
/**
 * callback from hook_block_view()
 */
function quotetype_ajax_stamp_block_form() {
  $form['authorize_stamp'] = array(
    '#type' => 'checkbox',
    '#title' => t('授权'),
    '#default_value' => variable_get('quote_default_value_company_name', ''),
    '#prefix' => '<div class="col-xs-1"><div class="btn btn-warning checkbox-authorize-stamp">',
    '#suffix' => '</div></div>',
    '#ajax' => array('callback' => 'quotetype_ajax_stamp_callback', 'effect' => 'fade',),
  );
  return $form;
}

/**
 * callback from quotetype_ajax_stamp_block_form()
 */
function quotetype_ajax_stamp_callback($form, &$form_state) {
  // Ajax framework commands
  $commands = array();

  // get check value, 1 for true, 0 for false
  $check_val = $form_state['values']['authorize_stamp'];
  
  // Ajax commands
  if ($check_val) {
    $commands[] = ajax_command_invoke('.checkbox-authorize-stamp', 'removeClass', array('btn-warning'));
    $commands[] = ajax_command_invoke('.checkbox-authorize-stamp', 'addClass', array('btn-primary'));
    $commands[] = ajax_command_invoke('.authorize-stamp-image', 'removeClass', array('element-invisible'));
  }
  else {
    $commands[] = ajax_command_invoke('.checkbox-authorize-stamp', 'removeClass', array('btn-primary'));
    $commands[] = ajax_command_invoke('.checkbox-authorize-stamp', 'addClass', array('btn-warning'));
    $commands[] = ajax_command_invoke('.authorize-stamp-image', 'addClass', array('element-invisible'));
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}