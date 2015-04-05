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
    $notify_status_key = 7;

    $OtherNotifyTerm = new OtherNotifyTerm($tid);
    // check "enable" status
    if ( !$OtherNotifyTerm->enableStatus() ) {
      return NULL;
    }

drupal_set_message(t('Send Mail -- 45'));
    $repair_nid_array = $this->allNotReturnRepairNid();

    $nodes = node_load_multiple($repair_nid_array);

    if (is_array($nodes)) {
      foreach ($nodes as $node) {
drupal_set_message(t('Send Mail -- 51'));
    watchdog('othernotify', t('Send Mail by "registerThreeDayNoFirstCheck" -- @nid'), array('@term' => $node->nid));
        $DateTime = new DateTime();
        $RepairInfo = new RepairInfo($node->nid);
        $repair_date = $RepairInfo->receiveDateTimeStamp();
        $condition_date = $repair_date + $OtherNotifyTerm->aheadTime();

        // condition,
        if ( !$RepairInfo->notifyStatus($notify_status_key) ) {
drupal_set_message(t('Send Mail -- 61'));
          if ($condition_date > $DateTime->getTimestamp()) {
drupal_set_message(t('Send Mail -- 63'));
            if ($RepairInfo->checkDateTimeStamp() == NULL) {
drupal_set_message(t('Send Mail -- 65'));
              $OtherNotifyTerm = new OtherNotifyTerm(129);
              $OtherNotifyTerm->sendNotifyMailByTerm($node->nid);

              $RepairInfo->updateNotifyStatus($notify_status_key);
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
    // $query->fieldCondition('field_repair_return_date', 'value', NULL, '=');

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