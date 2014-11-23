<?php

/**
 * callback from hook_form()
 * Bridge CallBack from '#process' of 'tableselect'
 */
function quotetype_tableselect_bridge_process_callback($form_element) {
  foreach (element_children($form_element) as $child_key) {
    if ('checkbox' == $form_element[$child_key]['#type']) {
      // Add ajax behavior as desired
      $form_element[$child_key]['#ajax'] = array(
        'callback' => 'quotetype_ajax_input_tableselect',
        'wrapper' => 'some-wrapper-id',
      );
    }
  }
  return $form_element;
}

/**
 * AJAX for 'tableselect'
 */
function quotetype_ajax_input_tableselect($form, &$form_state) {
  $output = '';
  $output .= '<table class="table table-striped">';
    $output .= '<thead>';
      $output .= '<tr>';
        $output .= '<th>#</th>';
        $output .= '<th>' . t('型号') . '</th>';
        $output .= '<th>' . t('价格') . '</th>';
      $output .= '</tr>';
    $output .= '</thead>';
    $output .= '<tbody>';

  // $form_state['values']['tableselect_nid'] is array, 
  // when checkbox is check on, "key" is nid, and "value" is nid also
  // when checkbox is check off, both "key" and "value" is 0
  $nid_sum = array_sum($form_state['values']['tableselect_nid']);
  if ($nid_sum > 0 ) {
    $nodes = node_load_multiple($form_state['values']['tableselect_nid']);
    $index = 1;
    foreach($nodes as $node) {
      if (isset($node->field_repair_device_type['und'][0]['tid'])) {
        $device_type_value = field_get_items('node', $node, 'field_repair_device_type');  
        $device_type_label = field_view_value('node', $node, 'field_repair_device_type', $device_type_value[0]);
      }
      $output .= '<tr><td>' . $index . '</td><td>' . $device_type_label['#title'] . '</td><td>' . $node->field_repair_quote_amount['und'][0]['value'] . '</td></tr>';
      $sum[] = $node->field_repair_quote_amount['und'][0]['value'];
      $index++;
    }
    $sumRepairAmount = number_format(array_sum($sum), 2, '.', '');
    $output .= '<tr><td></td><td>' .  t('折扣') . '</td><td class="quotation-js-insert-final-discount"></td></tr>';
    $output .= '<tr><td></td><td>' . t('总价') . '</td><td class="quotation-insert-markup-sum-price" value="' . $sumRepairAmount . '">' . $sumRepairAmount . '</td></tr>';
    
  }
  else {
    $output .= '<tr><td>No selected Device</td></tr>';
  }
    $output .= '</tbody>';
  $output .= '</table>';

  /**  - - - - - - - - - - - - - - - - - - - -  */
  // Ajax framework commands
  $commands = array();
  $commands[] = ajax_command_invoke('.page-add-new-quotation .quote-row-output-html', 'html', array($output));
  $commands[] = ajax_command_invoke('.page-add-new-quotation .form-item-sum-price input', 'val', array($sumRepairAmount));
  $commands[] = ajax_command_invoke('.page-add-new-quotation .form-item-basic-price input', 'val', array($sumRepairAmount));
  $commands[] = ajax_command_invoke('.page-add-new-quotation .quotation-js-insert-repair-nid input', 'val', array(''));
  if ($nid_sum > 0 ) {
    $commands[] = ajax_command_invoke('.page-add-new-quotation .add-repair-page-submit-wrapper #edit-submit', 'removeClass', array('disabled'));
    $nth = 0;
    foreach($nodes as $node) {
      $commands[] = ajax_command_invoke('.page-add-new-quotation .quotation-js-insert-repair-nid input:eq(' . $nth . ')', 'val', array($node->nid));
      $nth++;
    }
  }
  else {
    $commands[] = ajax_command_invoke('.page-add-new-quotation .add-repair-page-submit-wrapper #edit-submit', 'addClass', array('disabled'));
  }
  return array('#type' => 'ajax', '#commands' => $commands);
}

/**
 * EntityFieldQuery
 * @return
 * repair item with "quote status" is 0
 */
function quotetype_tableselect_content_callback() {
  // table header
  $header = array(
    'client_name' => t('Client Name'),
    'device_type' => t('Device Type'),
    'serial_number' => t('Serial Number'),
    'quote_amount' => t('Quote Amount'),
    'receive_date' => t('Receive Date'),
  );
  /**  - - - - - - - - - - - - - - - - - - - -  */
  // db_query all "repair" node with "Quote Status" is 0
  $query = new EntityFieldQuery;
  $query->entityCondition('entity_type', 'node')
    ->entityCondition('bundle', 'repair')
    ->propertyCondition('status', NODE_PUBLISHED)
    ->fieldCondition('field_repair_quote_status', 'value', 0)
    ->execute();
  $result = $query->execute();
  
  // check if have result
  if (isset($result['node'])) {
    $options = array();
    // $key is nid, and $row->nid is also nid
    $client_name_label = '';
    $device_type_label = '';
    $receive_date_label = '';
    foreach ($result['node'] as $key => $row) {
      if (isset($key)) {
        $node = node_load($key);
        if (isset($node->field_repair_client_name['und'][0]['target_id'])) {
          $client_name_value = field_get_items('node', $node, 'field_repair_client_name');  
          $client_name_label = field_view_value('node', $node, 'field_repair_client_name', $client_name_value[0]);
        }
        if (isset($node->field_repair_device_type['und'][0]['tid'])) {
          $device_type_value = field_get_items('node', $node, 'field_repair_device_type');  
          $device_type_label = field_view_value('node', $node, 'field_repair_device_type', $device_type_value[0]);
        }
        if (isset($node->field_repair_receive_date['und'][0]['value'])) {
          $receive_date_label = format_date($node->field_repair_receive_date['und'][0]['value'], 'year_mon_day');
        }
        
        $options[$key] = array(
          // 'key' must same with key used in the header
          'client_name'  => $client_name_label['#markup'],
          'device_type'  => $device_type_label['#title'],
          'serial_number'  => isset($node->field_repair_serial_number['und'][0]['safe_value']) ? $node->field_repair_serial_number['und'][0]['safe_value'] : '',
          'quote_amount' => isset($node->field_repair_quote_amount['und'][0]['value']) ? $node->field_repair_quote_amount['und'][0]['value'] : '',
          'receive_date' => $receive_date_label,
        );
      }
    }
  }
  
  $output = array();
  $output['header'] = $header;
  $output['options'] = $options;
  return $output;
}