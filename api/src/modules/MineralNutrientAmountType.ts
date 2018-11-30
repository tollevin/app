import {
  GraphQLObjectType,
  GraphQLNonNull,
  GraphQLID,
  GraphQLFloat
} from 'graphql';

import { Loader as ItemLoader } from '../model/ItemModel';

import * as Nutrient from './NutrientType';

import { fullTypeDefinition, nodeInterface } from '../interface/NodeInterface';

const TYPE_NAME = 'MineralNutrientAmount';

// idObj is {id: String, name: String}

export const {Type, Connection} = fullTypeDefinition(
  new GraphQLObjectType({
    name: TYPE_NAME,
    description: 'MineralNutrientAmount type',
    fields: () => ({
      id: {
        type: GraphQLNonNull(GraphQLID),
        resolve: async (idObj, args, context) => idObj.id,
      },
      nutrient: {
        type: GraphQLNonNull(Nutrient.Type),
        resolve: async (idObj, args, context) => idObj.name,
      },
      percentageDailyValue: {
        type: GraphQLNonNull(GraphQLFloat),
        resolve: async (idObj, args, context) => {
          const item = await ItemLoader.load(context, idObj.id);
          return item.nutrition_facts.PDV[idObj.name];
        },
      },
    }),
    interfaces: () => [nodeInterface],
  }),
);