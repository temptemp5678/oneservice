<?php
/**
 * @file
 */

/**
 * class
 */
class TermInfo {
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

  /** - - - - - Basic Object - - - - - - - - - -  - - - - -   */
  /**
   * @return Term Name
   */
  public function termName() {
    $output = NULL;
    if ($this->term) {
      $output = $this->term->name;
    }
    return $output;
  }
  /**
   * @return Term Vid
   */
  public function termVid() {
    $output = NULL;
    if ($this->term) {
      $output = $this->term->vid;
    }
    return $output;
  }
  /**
   * @return Term Description
   */
  public function termDescription() {
    $output = NULL;
    if ($this->term) {
      $output = $this->term->description;
    }
    return $output;
  }
}
