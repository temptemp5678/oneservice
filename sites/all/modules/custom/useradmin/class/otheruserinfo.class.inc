<?php
/**
 * @file
 */

/**
 * class
 */
class UserInfo {
  public $uid;
  public $user = NULL;

  /**
   * @parameter is uid
   */
  function __construct($uid){
    $this->uid = $uid;

    if (is_numeric($uid)) {
        $user = user_load($uid);
      if ($user) {
        $this->user = $user;
      }
    }
  }

  /** - - - - - user object - - - - - - - - - -  - - - - -   */
  /**
   * @return email
   *
   */
  public function userEmail() {
    $output = NULL;
    if (isset($this->user->mail)) {
      $output = $this->user->mail;
    }
    return $output;
  }

}
