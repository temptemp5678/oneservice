<?php
/**
 * @file
 */

/**
 * class
 */
class OtherNotifyMail {
  public $tid;
  public $term = NULL;

  /**
   * @parameter is tid
   */
  function __construct(){

  }

  /**
   * call from hook_cron()
   * @return
   */
  public function checkTermNotify() {
    if (!$this->term) {
      return NULL;
    }
    $output = NULL;
    if ($this->term) {
      $output = $this->term;
    }
    return $output;
  }


}
