<?php
/**
 * @file
 */

/**
 * class
 */
class RepairInfo {
  public $nid;
  public $node = NULL;

  /**
   * @parameter is nid
   */
  function __construct($nid){
    $this->nid = $nid;

    if (is_numeric($nid)) {
        $node = node_load($nid);
      if ($node) {
        $this->node = $node;
      }
    }
  }


  /** - - - - - Call Other Content Type - - - - - - - - - -  - - - - -   */
  /**
   * @return Quote Nid
   */
  public function quoteNid() {
    $repair_nid = $this->nid;
    $quote_nid = NULL;

    $query = new EntityFieldQuery;
    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'quote')
      ->propertyCondition('status', 1)
      ->fieldCondition('field_quote_repair_nid', 'value', $repair_nid);
    $result = $query->execute();
    if (isset($result['node'])) {
      $quote_nid = key($result['node']);
    }
    return $quote_nid;
  }

  /** - - - - - Text Field - - - - - - - - - -  - - - - -   */
  /**
   * @return Serial Number
   */
  public function serialNumber() {
    if (!$this->node) {
      return NULL;
    }
    $output = NULL;
    if (isset($this->node->field_repair_serial_number['und'][0]['safe_value'])) {
      $output = $this->node->field_repair_serial_number['und'][0]['safe_value'];
    }
    return $output;
  }

  /** - - - - - Decimal, Integer Field - - - - - - - - - -  - - - - -   */
  /**
   * @return quote Amount
   */
  public function quoteAmount() {
    if (!$this->node) {
      return NULL;
    }
    $output = NULL;
    if (isset($this->node->field_repair_quote_amount['und'][0]['value'])) {
      $output = $this->node->field_repair_quote_amount['und'][0]['value'];
    }
    return $output;
  }


  /** - - - - - Boolean Field - - - - - - - - - -  - - - - -   */
  /**
   * @return quote Status
   */
  public function quoteStatus() {
    if (!$this->node) {
      return NULL;
    }
    $output = NULL;
    if (isset($this->node->field_repair_quote_status['und'][0]['value'])) {
      $output = $this->node->field_repair_quote_status['und'][0]['value'];
    }
    return $output;
  }

  /** - - - - - Term reference Field - - - - - - - - - -  - - - - -   */
  /**
   * @return Device Type
   */
  public function deviceType() {
    if (!$this->node) {
      return NULL;
    }
    $output = NULL;
    if (isset($this->node->field_repair_device_type['und'][0]['tid'])) {
      $output = $this->node->field_repair_device_type['und'][0]['tid'];
    }
    return $output;
  }


  /** - - - - - Date (Unix timestamp) Field - - - - - - - - - -  - - - - -   */
  /**
   * @return Receive Date Time Stamp
   */
  public function receiveDateTimeStamp() {
    $output = NULL;
    if (isset($this->node->field_repair_receive_date['und'][0]['value'])) {
      $output = $this->node->field_repair_receive_date['und'][0]['value'];
    }
    return $output;
  }
  /**
   * @return Receive Date
   */
  public function receiveDateFormat() {
    $output = NULL;
    $stamp = $this->receiveDateTimeStamp();
    if (!empty($stamp)) {
      $output = format_date($stamp, 'custom', 'Y-m-d');
    }
    return $output;
  }

  /**
   * @return check Date Time Stamp
   */
  public function checkDateTimeStamp() {
    $output = NULL;
    if (isset($this->node->field_repair_check_date['und'][0]['value'])) {
      $output = $this->node->field_repair_check_date['und'][0]['value'];
    }
    return $output;
  }
  /**
   * @return Receive Date
   */
  public function checkDateFormat() {
    $output = NULL;
    $stamp = $this->checkDateTimeStamp();
    if (!empty($stamp)) {
      $output = format_date($stamp, 'custom', 'Y-m-d');
    }
    return $output;
  }

  /**
   * @return return Date Time Stamp
   */
  public function returnDateTimeStamp() {
    $output = NULL;
    if (isset($this->node->field_repair_return_date['und'][0]['value'])) {
      $output = $this->node->field_repair_return_date['und'][0]['value'];
    }
    return $output;
  }
  /**
   * @return Receive Date
   */
  public function returnDateFormat() {
    $output = NULL;
    $stamp = $this->returnDateTimeStamp();
    if (!empty($stamp)) {
      $output = format_date($stamp, 'custom', 'Y-m-d');
    }
    return $output;
  }

  /** - - - - - Boolean Field - - - - - - - - - -  - - - - -   */
  /**
   * @return Boolean
   *  repair Notify Status
   */
  public function notifyTermStatus($tid) {
    // like "field_repair_notifyterm_132"
    $notify_term_field = 'field_repair_notifyterm_' . $tid;

    $output = NULL;
    if (isset($this->node->{$notify_term_field}['und'][0]['value'])) {
      $output = $this->node->{$notify_term_field}['und'][0]['value'];
    }
    return $output;
  }

  /** - - - - - Update Field - - - - - - - - - -  - - - - -   */
  /**
   * @update Boolean
   *  repair Notify Status
   */
  public function updateNotifyTermStatus($tid) {
    // like "field_repair_notifyterm_132"
    $notify_term_field = 'field_repair_notifyterm_' . $tid;

    $this->node->{$notify_term_field}['und'][0]['value'] = TRUE;

    field_attach_presave('node', $this->node);
    field_attach_update('node', $this->node);
  }
}
