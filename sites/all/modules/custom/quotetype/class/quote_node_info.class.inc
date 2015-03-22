<?php
/**
 * @file
 */

/**
 * class
 */
class QuoteInfo {
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
  
  /** - - - - - Text Field - - - - - - - - - -  - - - - -   */
  /**
   * @return Client Name
   */
  public function clientName() {
    if (!$this->term) {
      return NULL;
    }
    $output = NULL;
    if (isset($this->term->field_quote_client_name['und'][0]['safe_value'])) {
      $output = $this->term->field_quote_client_name['und'][0]['safe_value'];
    }
    return $output;
  }
  
  /** - - - - - Decimal, Integer Field - - - - - - - - - -  - - - - -   */
  /**
   * @return Repair NID
   */
  public function repairNid() {
    if (!$this->term) {
      return NULL;
    }
    $output = NULL;
    if (isset($this->term->field_quote_repair_nid['und'][0]['value'])) {
      $output = $this->term->field_quote_repair_nid['und'][0]['value'];
    }
    return $output;
  }
  
  /**
   * @return Sum Price
   */
  public function sumPrice() {
    if (!$this->term) {
      return NULL;
    }
    $output = NULL;
    if (isset($this->term->field_quote_sum_price['und'][0]['value'])) {
      $output = $this->term->field_quote_sum_price['und'][0]['value'];
    }
    return $output;
  }
  
  /**
   * @return Warranty Day
   */
  public function warrantyDay() {
    if (!$this->term) {
      return NULL;
    }
    $output = NULL;
    if (isset($this->term->field_quote_warranty_day['und'][0]['value'])) {
      $output = $this->term->field_quote_warranty_day['und'][0]['value'];
    }
    return $output;
  }
  
  /** - - - - - Boolean Field - - - - - - - - - -  - - - - -   */
  /**
   * @return Authorize Stamp
   */
  public function authorizeStamp() {
    if (!$this->node) {
      return NULL;
    }
  
    if (isset($this->node->field_quote_authorize_stamp['und'][0]['value'])) {
      $output = $this->node->field_quote_authorize_stamp['und'][0]['value'];
    }
    return $output;
  }
  
  /** - - - - - Term reference Field - - - - - - - - - -  - - - - -   */
  /**
   * @return Company Name
   */
  public function companyNameTid() {
    if (!$this->node) {
      return NULL;
    }
  
    if (isset($this->node->field_quote_company_name['und'][0]['tid'])) {
      $output = $this->node->field_quote_company_name['und'][0]['tid'];
    }
    return $output;
  }
  
  /**
   * @return Program Unit Name
   */
  public function companyNameName() {
    if (!$this->node) {
      return NULL;
    }
    
    $unit_term = taxonomy_term_load($this->unitTid());
    $output = NULL;
    if ($unit_term) {
      $output = $unit_term->name;
    }
    return $output;
  }
    
  /** - - - - - Date (Unix timestamp) Field - - - - - - - - - -  - - - - -   */
  /**
   * @return Quote Date
   */
  public function quoteDateTimeStamp() {
    if (!$this->node) {
      return NULL;
    }
    
    $output = NULL;
    if (isset($this->node->field_quote_create_date['und'][0]['value'])) {
      $output = $this->node->field_quote_create_date['und'][0]['value'];
    }
    return $output;
  }
  /**
   * @return Quote Date
   */
  public function quoteDateFormat() {
    if (!$this->node) {
      return NULL;
    }
    
    $output = NULL;
    $stamp = $this->quoteDateTimeStamp();
    if (!empty($stamp)) {
      $output = format_date($stamp, 'custom', 'Y-m-d');
    }
    return $output;
  }
}
