<?php
/**
 * @file
 */

/**
 * class
 */
class OtherNotifyMail {
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
   * @return Term notify Name
   *
   * Device Register when the repair node create
   * term tid = 128
   */
  public function repairNodeCreate() {
    if (!$this->node) {
      return NULL;
    }

    $NotifyTermInfo = new NotifyTermInfo(128);

    $to = $NotifyTermInfo->mailTo();   // to e-mail address
    $from = "test@example.com"; // from e-mail address

    $other_body = $this->node->title . ' has created';

    $subject = $NotifyTermInfo->mailTitle();
    $body = $NotifyTermInfo->mailContent() . $other_body;

    //params is the array passed to hook_mail function
    $params = array(
      'subject' => $subject,
      'body' => $body,
    );

    $module = 'othernotify';
    $key = 'repair-node-create';
    $language = language_default();
    // drupal_mail send email
    drupal_mail($module, $key, $to, $language, $params, $from);
  }

}
