<?php

/**
 * @file
 * This template is used to print a single field in a view.
 *
 * It is not actually used in default Views, as this is registered as a theme
 * function which has better performance. For single overrides, the template is
 * perfectly okay.
 *
 * Variables available:
 * - $view: The view object
 * - $field: The field handler object that can process the input
 * - $row: The raw SQL result that can be used
 * - $output: The processed output that will normally be used.
 *
 * When fetching output from the $row, this construct should be used:
 * $data = $row->{$field->field_alias}
 *
 * The above will guarantee that you'll always get the correct data,
 * regardless of any changes in the aliasing that might happen if
 * the view is modified.
 */
?>
<?php // print $output; ?>
<?php
  /**
   * output is "key" instead of "value" on Views setting 
   * Key value is 1 that Authorize Stamp, 0 is not yet 
   * 1 to print Authorize Stamp, 0 is empty 
   */
  $nid = $row->nid;
  $QuoteInfo = new QuoteInfo($nid);
  $company_term_tid = $QuoteInfo->companyNameTid();
  
  $CompanyTermInfo = new CompanyTermInfo($company_term_tid);
  $stamp_image = $CompanyTermInfo->authorizeStampImage('24px', '24px');
  
  $new_output = '';
  // $output is Boolean for "field_quote_authorize_stamp" field
  if ($output) {
    $new_output = $stamp_image;
  }
  print $new_output;
?>