import {
  GraphQLObjectType,
  GraphQLNonNull,
  GraphQLID
} from 'graphql';

import { fullTypeDefinition, nodeInterface } from '../interface/NodeInterface';

const TYPE_NAME = 'DeliveryWindow';

// idObj is id: String

export const {Type, Connection} = fullTypeDefinition(
  new GraphQLObjectType({
    name: TYPE_NAME,
    description: 'Delivery Window type',
    fields: () => ({
      id: {
        type: GraphQLNonNull(GraphQLID),
        resolve: async (idObj, args, context) => "1",
      },
    }),
    interfaces: () => [nodeInterface],
  }),
);
