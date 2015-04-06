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
   * @to call different term notification with time validate
   */
  public function checkCronNotify() {
    $this->registerThreeDayNoFirstCheck();
  }

    /**
   * @return
   *
   * After Device Register 3 days and No one to do First Check
   * term tid = 129
   */
  public function registerThreeDayNoFirstCheck() {
    $tid = 129;

    $OtherNotifyTerm = new OtherNotifyTerm($tid);
    // check "enable" status
    if ( !$OtherNotifyTerm->enableStatus() ) {
      return NULL;
    }

    $repair_nid_array = $this->allNotReturnRepairNid();

    $nodes = node_load_multiple($repair_nid_array);

    if (is_array($nodes)) {
      foreach ($nodes as $node) {
        $DateTime = new DateTime();
        $RepairInfo = new RepairInfo($node->nid);
        $repair_date = $RepairInfo->receiveDateTimeStamp();
        $condition_date = $repair_date + $OtherNotifyTerm->aheadTime();

        // condition,
        if ( $RepairInfo->returnDateTimeStamp() == NULL ) {
          if ( !$RepairInfo->notifyTermStatus($tid) ) {
            if ($condition_date < $DateTime->getTimestamp()) {
              if ($RepairInfo->checkDateTimeStamp() == NULL) {

                $message = 'Send Mail -- node -- ' . $node->nid;
  drupal_set_message($message);
                $OtherNotifyTerm = new OtherNotifyTerm(129);
                $OtherNotifyTerm->sendNotifyMailByTerm($node->nid);

                // $RepairInfo->updateNotifyTermStatus($tid);
                watchdog('othernotify', t('Send Mail for "registerThreeDayNoFirstCheck" -- @nid'), array('@nid' => $node->nid));
              }
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
    // $query->fieldCondition('field_repair_return_date', 'value', 1, '<');

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