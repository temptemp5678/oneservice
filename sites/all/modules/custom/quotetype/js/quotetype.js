(function ($) {
  Drupal.behaviors.zencharts = {
    attach: function (context, settings) {
      /**
       *
       */
      jQuery('.view-repair-list-no-quote-yet .views-field-nothing input').on('click', function() {
         // console.log(jQuery(this.checked)[0]);
         // console.log(jQuery(this.val());
         checkSelectedLength();
      });

      /**
       * check length for Checkbox,
       * if "length" is 0 return warning text
       * if "length" is more than 0, call function to return HTML table output
       */
      function checkSelectedLength() {
        var rowContent = [];
        jQuery('.view-repair-list-no-quote-yet .views-field-nothing input').each(function () {
           if (this.checked) {
             rowContent.push(jQuery(this).val());
           }
        });
        
        var output = '';
        // console.log(rowContent);
        if (rowContent.length > 0 ) {
          jQuery.each(rowContent, function( index, value ) {
            output += '<p>' + value + '</p>';
          });
        }
        else {
          output = '<p>No selected Device</p>';
        }
        
        jQuery('.quote-row-output-html div').html(output);
        // write HTML
      }
      
      /** - - - - - - - - - - - - - - - - - - - -  */


    // --- end for attach: function()
    }
  };
})(jQuery);