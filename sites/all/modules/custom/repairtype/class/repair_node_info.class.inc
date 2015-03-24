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
}
