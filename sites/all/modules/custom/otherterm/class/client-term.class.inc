<?php
/**
 * @file
 */

/**
 * class
 */
class ClientTermInfo {
  public $tid;
  public $term = NULL;

  /**
   * @parameter is tid
   */
  function __construct($tid){
    $this->tid = $tid;

    if (is_numeric($tid)) {
        $term = taxonomy_term_load($tid);
      if ($term) {
        $this->term = $term;
      }
    }
  }

  /**
   * @return Term client Name
   */
  public function clientName() {
    if (!$this->term) {
      return NULL;
    }
    $output = NULL;
    if ($this->term) {
      $output = $this->term->name;
    }
    return $output;
  }

  /** - - - - - Entity Reference - - - - - - - - - -  - - - - -   */
  /**
   * @return array
   *  client Bank Name
   */
  public function clientBundleSales() {
    if (!$this->term) {
      return NULL;
    }
    $output = NULL;
    if (isset($this->term->field_client_bundlesales['und'][0]['target_id'])) {
      foreach ($this->term->field_client_bundlesales['und'] as $key => $row) {
        $output[] = $row['target_id'];
      }
    }
    return $output;
  }

}
