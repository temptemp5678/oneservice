(function ($) {
  Drupal.behaviors.zencharts = {
    attach: function (context, settings) {
      /**
       * Check box to select "repair item"
       */
      jQuery('.view-repair-list-no-quote-yet .views-field-nothing input').on('click', function() {
         checkSelectedLength();
      });

      /**
       * check length for Checkbox,
       * if "length" is 0 return warning text
       * if "length" is more than 0, call function to return HTML table output
       */
      function checkSelectedLength() {
        var deviceType = [];
        var repairAmount = [];
        var nidSelected = [];
        jQuery('.view-repair-list-no-quote-yet .views-field-nothing input').each(function () {
           if (this.checked) {
             deviceType.push(jQuery(this).attr("devicetype"));
             repairAmount.push(jQuery(this).attr("amount"));
             nidSelected.push(jQuery(this).attr("nid"));
           }
        });
        // sum for "repairAmount"
        var sumRepairAmount = 0;
        $.each(repairAmount,function() {
          sumRepairAmount += parseFloat(this);
        });
          sumRepairAmount = sumRepairAmount.toFixed(2);
        
        var output = '';
            output += '<table class="table table-striped">';
              output += '<thead>';
                output += '<tr>';
                  output += '<th>#</th>';
                  output += '<th>' + Drupal.t('型号') + '</th>';
                  output += '<th>' + Drupal.t('价格') + '</th>';
                output += '</tr>';
              output += '</thead>';
              output += '<tbody>';

        if (nidSelected.length > 0 ) {
          jQuery.each(nidSelected, function( index, value ) {
                output += '<tr><td>' + (index + 1) + '</td><td>' + deviceType[index] + '</td><td>' + repairAmount[index] + '</td></tr>';
          });
                output += '<tr><td></td><td>' + Drupal.t('折扣') + '</td><td class="quotation-js-insert-final-discount"></td></tr>';
                output += '<tr><td></td><td>' + Drupal.t('总价') + '</td><td class="quotation-insert-markup-sum-price" value="' + sumRepairAmount + '">' + sumRepairAmount + '</td></tr>';
        }
        else {
                output += '<tr><td>No selected Device</td></tr>';
        }
              output += '</tbody>';
            output += '</table>';
        
        // insert "sumRepairAmount"
        jQuery('.page-add-new-quotation .form-item-sum-price input').val(sumRepairAmount);
        jQuery('.page-add-new-quotation .form-item-basic-price input').val(sumRepairAmount);
        // insert Output Table for Quotation
        jQuery('.page-add-new-quotation .quote-row-output-html').html(output);
        
        /** - - - - - - - - - - - - - - - - - - - -  */
        
        // Insert NID of "repair" to hide field
        jQuery('#quotetype-add-quote-form .quotation-js-insert-repair-nid input').each(function () {
          // firstly, empty all value for NID field
          jQuery(this).val('');
        });
        if (nidSelected.length > 0) {
          jQuery.each(nidSelected, function( index, value ) {
            // insert NID
            jQuery('#quotetype-add-quote-form .quotation-js-insert-repair-nid input').eq(index).val(value);
          });
        }
      }
      
      /**
       *  quote table header
       */
      function quoteTable() {
      
      }
      
      /** - - - - - - - - - - - - - - - - - - - -  */


    // --- end for attach: function()
    }
  };
})(jQuery);