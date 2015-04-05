<?php
/**
 * @file
 */

/**
 * class
 */
class OtherNotifyNode {
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

  /**
   * @return
   *
   * Device Register when the repair node create
   * term tid = 128
   */
  public function repairNodeCreate() {
    if (!$this->node) {
      return NULL;
    }

    $OtherNotifyTerm = new OtherNotifyTerm(128);
    $OtherNotifyTerm->sendNotifyMailByTerm();
  }

}
