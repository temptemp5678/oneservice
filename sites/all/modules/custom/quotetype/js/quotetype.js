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
        var rowContent = [];
        var nidSelected = [];
        jQuery('.view-repair-list-no-quote-yet .views-field-nothing input').each(function () {
           if (this.checked) {
             rowContent.push(jQuery(this).val());
             nidSelected.push(jQuery(this).attr("nid"));
           }
        });
        
        var output = '';
            output += '<table class="table table-striped">';
              output += '<caption>Optional table caption.</caption>'
              output += '<thead>';
                output += '<tr>';
                  output += '<th>#</th>';
                  output += '<th>' + Drupal.t('型号') + '</th>';
                  output += '<th>' + Drupal.t('价格') + '</th>';
                output += '</tr>';
              output += '</thead>';
              output += '<tbody>';

        if (rowContent.length > 0 ) {
          jQuery.each(rowContent, function( index, value ) {
                output += '<tr><td>' + value + '</td></tr>';
          });
        }
        else {
                output += '<tr><td>No selected Device</td></tr>';
        }
              output += '</tbody>';
              output += '<caption>Optional table caption.</caption>'
            output += '</table>';
        
        // insert HTML
        jQuery('.quote-row-output-html').html(output);
        
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