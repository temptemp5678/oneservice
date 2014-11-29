<?php
/**
 * See more at: http://dominiquedecooman.com/drupal-7-tip-create-custom-views-access-plugin
 */

/**
 * Access plugin that provides property based access control.
 */
class otherviews_access_plugin extends views_plugin_access {
  function summary_title() {
    return t('Custom access plugin');
  } // summary_title()

  /** * Determine if the current user has access or not. */
  function access($account) {
    return otherviews_access($account);
  }

  function get_access_callback() {
    return array('otherviews_access', array());
  }
}