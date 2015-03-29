<?php
/**
 * @file
 */

/**
 * class
 */
class NotifyTermInfo {
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
   * @return Term notify Name
   */
  public function notifyName() {
    if (!$this->term) {
      return NULL;
    }
    $output = NULL;
    if ($this->term) {
      $output = $this->term;
    }
    return $output;
  }

  /**
   * @return array
   *  all notify Mail To Receiver
   */
  public function mailTo() {
    if (!$this->term) {
      return NULL;
    }
    $output = NULL;
    if (isset($this->term->field_notify_mail_to['und'][0]['safe_value'])) {
      $output[] = $this->term->field_notify_mail_to['und'][0]['safe_value'];
      // foreach ($this->term->field_notify_mail_to['und'] as $key => $row) {
        // $output[] = $row['safe_value'];
      // }
    }
    
    if (is_array($output)) {
      // convert array to like "user@example.com, user2@example.com"
      $output = implode(',', $output);
    }
    return $output;
  }

  /**
   * @return notify Mail Title
   */
  public function mailTitle() {
    if (!$this->term) {
      return NULL;
    }
    $output = NULL;
    if (isset($this->term->field_notify_mail_title['und'][0]['safe_value'])) {
      $output = $this->term->field_notify_mail_title['und'][0]['safe_value'];
    }
    return $output;
  }

  /**
   * @return notify Mail Content
   */
  public function mailContent() {
    if (!$this->term) {
      return NULL;
    }
    $output = NULL;
    if (isset($this->term->field_notify_mail_content['und'][0]['safe_value'])) {
      $output = $this->term->field_notify_mail_content['und'][0]['safe_value'];
    }
    return $output;
  }

  /**
   * @return notify Ahead of Time
   */
  public function aheadTime() {
    if (!$this->term) {
      return NULL;
    }
    $output = NULL;
    if (isset($this->term->field_notify_ahead_time['und'][0]['value'])) {
      $output = $this->term->field_notify_ahead_time['und'][0]['value'];
    }
    return $output;
  }

  /**
   * @return notify Ahead of Time
   */
  public function enableStatus() {
    if (!$this->term) {
      return NULL;
    }
    $output = NULL;
    if (isset($this->term->field_notify_enable_status['und'][0]['value'])) {
      $output = $this->term->field_notify_enable_status['und'][0]['value'];
    }
    return $output;
  }


}
