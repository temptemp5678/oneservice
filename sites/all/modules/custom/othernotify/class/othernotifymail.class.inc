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
   *
   * @to call different term with time validate
   */
  public function checkCronNotify() {
    $this->registerThreeDayNoFirstCheck()

  }

    /**
   * @return
   *
   * After Device Register 3 days and No one to do First Check
   * term tid = 129
   */
  public function registerThreeDayNoFirstCheck() {
    $tid = 129;
    $notify_status_key = 2;

    $OtherNotifyTerm = new OtherNotifyTerm($tid);
    // check "enable" status
    if ( !$OtherNotifyTerm->enableStatus() ) {
      return NULL;
    }

    $repair_nid_array = $this->allNotReturnRepairNid();

    $nodes = node_load_multiple($repair_nid_array);

    if (is_array($nodes) {
      foreach ($nodes as $node) {
        $DateTime = new DateTime();

        $RepairInfo = new RepairInfo($node->nid);
        $repair_date = $RepairInfo->receiveDateTimeStamp();
        $condition_date = $repair_date + $OtherNotifyTerm->aheadTime();

        // condition,
        if ($condition_date > $DateTime->getTimestamp()) {
          if ($RepairInfo->checkDateTimeStamp() > 0) {
            if ( !$RepairInfo->notifyStatus($notify_status_key) ) {
              $OtherNotifyTerm = new OtherNotifyTerm(129);
              $OtherNotifyTerm->sendNotifyMailByTerm();

              $RepairInfo->notifyStatus($updateNotifyStatus);
            }
          }
        }
      }
    }
  }

  /**
   * @parameter array,
   *  Meeting Nid
   * @return array, all Repair not Return yet Node NID
   * bundle is repair
   */
  public function allNotReturnRepairNid() {
    $query = new EntityFieldQuery;
    $query->entityCondition('entity_type', 'node')
      ->entityCondition('bundle', 'repair')
      ->propertyCondition('status', NODE_PUBLISHED);
    // return date still empty
    $query->fieldCondition('field_repair_return_date', 'value', NULL, '=');

    $result = $query->execute();

    $repair_nid_array = NULL;
    if (isset($result['node'])) {
      if (count($result['node']) > 0 ) {
        $repair_nid_array = array_keys($result['node']);
      }
    }
    return $repair_nid_array;
  }

}