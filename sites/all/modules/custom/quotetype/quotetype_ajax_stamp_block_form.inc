<?php
/**
 * callback from hook_block_view()
 */
function quotetype_ajax_stamp_block_form() {
  $node = menu_get_object();
  
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
      '#title' => t('授权'),
      '#default_value' => $stamp_value,
      '#prefix' => '<div class="col-xs-2"><div class="btn ' . $stamp_class . ' checkbox-authorize-stamp">',
      '#suffix' => '</div></div>',
      '#ajax' => array('callback' => 'quotetype_ajax_stamp_callback', 'effect' => 'fade',),
    );
  }
  return $form;
}

/**
 * callback from quotetype_ajax_stamp_block_form()
 */
function quotetype_ajax_stamp_callback($form, &$form_state) {
  /**
   * 
  // update Authorize Stamp field value
  $node = menu_get_object();
  if (isset($node)) {
    $field_language = field_language('node', $node, 'field_quote_authorize_stamp');
    $node->field_quote_authorize_stamp[$field_language][0]['value'] = $form_state['values']['authorize_stamp'];
    //field_attach_presave('node', $repair_node);
    field_attach_update('node', $node);
  }
   */
  
  /** - - - - - - - - - - - - - - - - - - - -  */
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