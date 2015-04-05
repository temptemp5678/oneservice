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

  /** - - - - - Boolean Field - - - - - - - - - -  - - - - -   */
  /**
   * @return Boolean
   *  repair Notify Status
   */
  public function notifyStatus($key = 0) {
    $output = NULL;
    if (isset($this->node->field_repair_notify_status['und'][$key]['value'])) {
      $output = $this->node->field_repair_notify_status['und'][$key]['value'];
    }
    return $output;
  }

  /**
   * @return Boolean
   *  Update repair Notify Status as TRUE
   */
  public function UpdateNotifyStatus($key = 0) {
    $this->node->nid;
  }
}
